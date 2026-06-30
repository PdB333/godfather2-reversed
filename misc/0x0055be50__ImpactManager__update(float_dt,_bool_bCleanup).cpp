// FUNC_NAME: ImpactManager::update(float dt, bool bCleanup)

// Reconstructed C++ for function at 0x0055be50
// Based on Ghidra decompilation of The Godfather 2 (EA EARS engine)
// This function updates impact effects (e.g., bullet impacts, explosions)

#include <cstdint>

// Forward declarations
class SomeRefCountedObject; // Object with vtable at +0, ref count at +4
class ImpactListNode;       // Node in a linked list, size 0x40, vtable PTR_LAB_00e3a070
class SpawnPoint;          // Array element at offset 0xd8+0x48, size 0xc0
class TimelineEntry;       // Array element at offset 0xda+0x8c, size 0x28

// Constants (guessed from data refs, actual values unknown)
const float GLOBAL_ZERO = 0.0f; // DAT_00e2b334 (used as zero)
const float GLOBAL_ONE = 1.0f;  // DAT_00e2b1a4 (used as max threshold)
const float DAT_00e44564 = 0.0f; // Some constant, maybe initial timer offset
const float DAT_00e44718 = 0.5f; // Interpolation factor (guess)
const float DAT_00e2cd54 = 0.2f; // Another interpolation factor (guess)

class ImpactManager {
public:
    // Virtual table at +0
    // Known vtbl offsets used:
    // 0x198: bool isActive()   ?
    // 0x250: void getCameraVector(int index, float* outVec4)
    // 0x58:  int createEffect(int param, ...)

    struct ImpactSlot {
        int32_t state;           // +0x1d0: 0=idle, 1=waiting, 2=active
        SomeRefCountedObject* pRefObj; // +0x1d1: ref-counted object (particle/ghost)
        void* pListNode;         // +0x1d2: pointer to linked list node (ImpactListNode)
        void* pDecalObj;         // +0x1d3: pointer to decal or secondary effect
        float timer;             // +0x1d4: timer (stored as int, used as float)
    };

    // Offsets from this pointer
    // +0x34: Some 4x4 matrix? (64 bytes, copied to effect)
    // +0xd8: pointer to SpawnPointArray?
    // +0xda: pointer to TimelineArray?
    // +0x1cc - 0x1cf: flags for secondary effect
    // +0x1d0: array of 4 ImpactSlot structs (20 bytes each → 80 bytes)
    // +0x1e4, 0x1e5, 0x1e6, 0x1e7: timing parameters (lifetime, min, max)

    void update(float dt, bool bCleanup) {
        // Virtual call: check if this manager is active
        if (!((bool(*)(ImpactManager*))(*(void***)this)[0x198/4])(this))
            return;

        if (bCleanup) {
            // Cleanup path: release all 4 impact slots
            int* pSlot = (int*)&this->slots[0];
            for (int i = 0; i < 4; i++) {
                // FUN_0055af20 - cleanup helper? (unknown)
                extern void cleanupHelper(); // Stub
                cleanupHelper();

                SomeRefCountedObject* obj = (SomeRefCountedObject*)*pSlot;
                if (obj) {
                    int* refCount = (int*)obj + 1;
                    (*refCount)--;
                    if (*refCount == 0) {
                        // Virtual destructor at vtable+4
                        (*(void(**)(SomeRefCountedObject*))(*obj + 4))(obj);
                    }
                    *pSlot = 0;
                }
                pSlot += 5; // move to next slot (20 bytes)
            }
            return;
        }

        // Update path
        float fVar12 = GLOBAL_ONE;
        float fStack_60 = GLOBAL_ZERO;
        float fStack_5c = GLOBAL_ZERO;
        float fStack_58 = GLOBAL_ZERO;
        float fStack_54 = GLOBAL_ZERO;

        int spawnIndex = 0;          // iStack_118
        int timelineOffset = 0;      // iStack_10c
        int spawnByteOffset = 0;     // iStack_108
        int slotIndex = 0;           // index into slots (implicit via piVar6)

        // We have 4 spawn points
        while (spawnByteOffset < 0x300) { // 4 * 0xc0 = 0x300
            ImpactSlot* slot = &this->slots[slotIndex];
            float* spawnData = (float*)(*(this->spawnPointArray) + 0x48) + spawnByteOffset/4;

            // fVar10 = normalized lifetime (0..1) based on spawn data
            float fVar10;
            if (spawnData[9] == 0.0f) {
                fVar10 = 0.0f;
            } else {
                float life = spawnData[0x2a] - (float)this->lifetimeMin; // param_1[0x1e6]
                if (life <= 0.0f) {
                    fVar10 = 0.0f;
                } else {
                    fVar10 = life / ((float)this->lifetimeMax - (float)this->lifetimeMin);
                }
            }

            // State machine for this slot
            if (slot->state == 1) {
                if (fVar10 <= 0.0f) {
                    slot->state = 0;
                } else {
                    float newTimer = (float)slot->timer + dt;
                    slot->timer = newTimer;
                    if (newTimer > 0.0f) {
                        slot->state = 2;
                    }
                }
            } else if (slot->state == 2) {
                if (fVar10 <= 0.0f) {
                    slot->state = 0;
                }
            } else {
                // state == 0
                if (fVar10 > 0.0f) {
                    slot->state = 1;
                    slot->timer = (float)(int)(DAT_00e44564 - (float)this->someParam); // param_1[0x1e4]
                }
            }

            // Get camera vector from virtual function
            float cameraVec[4] = {0,0,0,0};
            (*(void(**)(ImpactManager*, int, float*))(*(void***)this)[0x250/4])(this, spawnIndex, cameraVec);

            // Get timeline value (interpolation factor)
            float timelineVal = *(float*)(*(this->timelineArray) + 0x8c + timelineOffset);

            // Compute base position from spawn data (using zero multipliers)
            float baseX = spawnData[4] * fStack_60 + spawnData[0];
            float baseY = spawnData[5] * fStack_5c + spawnData[1];
            float baseZ = spawnData[6] * fStack_58 + spawnData[2];

            // Two interpolation results: near (fVar9) and far (fVar12)
            float fVar9 = timelineVal * DAT_00e44718;
            float fVar12New = timelineVal * DAT_00e2cd54;

            float nearPosX = fVar9 * cameraVec[0] + baseX;
            float nearPosY = fVar9 * cameraVec[1] + baseY;
            float nearPosZ = fVar9 * cameraVec[2] + baseZ;

            float farPosX = fVar12New * cameraVec[0] + baseX;
            float farPosY = fVar12New * cameraVec[1] + baseY;
            float farPosZ = fVar12New * cameraVec[2] + baseZ;

            if (slot->state == 2) {
                // Active: ensure ref counted object exists
                if (slot->pRefObj == nullptr) {
                    // Allocate via global allocator
                    extern void* getAllocator(); // FUN_009c8f80
                    void* alloc = getAllocator();
                    int params[] = {2, 0x10, 0};
                    void* newObj = (*(void*(*)(void*, int, int*))*(void**)alloc)(0x40, params);
                    if (newObj == nullptr) {
                        slot->pRefObj = nullptr;
                        // _DAT_00000004++; // leaked count (unused here)
                    } else {
                        // Initialize object (vtable PTR_LAB_00e3a070)
                        *(uint32_t*)(newObj+4) = 0; // refCount? actually set to 0
                        *(void**)newObj = &PTR_LAB_00e3a070; // vtable
                        // Zero out rest (offsets 0x10..0x3c)
                        for (int i=0; i<10; i++) ((uint32_t*)newObj)[4+i] = 0;
                        slot->pRefObj = (SomeRefCountedObject*)newObj;
                        // Increase refCount
                        (*(int*)(newObj+4))++;
                    }
                }

                // Create linked list node if not exists
                if (slot->pListNode == nullptr) {
                    // Copy matrix from this+0x34 (64 bytes)
                    float matrixCopy[16];
                    float* src = (float*)(this->transformMatrix);
                    for (int i=0; i<16; i++) matrixCopy[i] = src[i];
                    // Stack allocation for matrix copy function (FUN_0044b4e0)
                    // In original: copied to local array auStack_50
                    // Actually FUN_0044b4e0 copies 64 bytes from this+0x34 to auStack_50
                    // Then used with virtual call to create effect
                    uint32_t someHandle;
                    {
                        int params[] = {1};
                        someHandle = (*(uint32_t(*)(ImpactManager*, int, int*))*(void***)this)[0x58/4])(this, 0, params);
                    }
                    // Call list insertion (FUN_004df270)
                    // This creates a new ImpactListNode and links it
                    void* newNode = createListNode(someHandle, (float*)auStack_50);
                    if (slot->pListNode != 0) {
                        // Clear existing? Actually they set to zero then assign
                        *(void**)(slot->pListNode + 8) = 0;
                        slot->pListNode = 0;
                    }
                    slot->pListNode = newNode;
                    if (newNode) {
                        *(void**)((uint8_t*)newNode + 8) = &slot->pListNode; // linked list next?
                        // The original sets next pointer in the list
                    }
                    // Clear temporary list pointer
                    // (the newly created node is now owned by the slot)
                }
            } else {
                // Not active: clear flags on decal object if exists
                if (slot->pDecalObj != nullptr) {
                    // Check bit flag at offset 0xc
                    if (!(*(uint32_t*)(slot->pDecalObj + 0xc) & 0x20000)) {
                        *(uint32_t*)(slot->pDecalObj + 0xc) |= 0x20000;
                        extern void flagUpdate(); // FUN_0051b120
                        flagUpdate();
                    }
                    // Clear another flag
                    *(uint32_t*)(slot->pDecalObj + 0xc) &= ~0x40000;
                }
                fVar10 = 0.0f; // clear alpha?
            }

            // Update ref counted object with positions
            SomeRefCountedObject* refObj = slot->pRefObj;
            if (refObj != nullptr) {
                // Store far position (near/interpolated) and near? Actually they store both?
                // Offset layout for refObj: +0x10 farPos, +0x20 nearPos, +0x30 alpha
                *(float*)((uint8_t*)refObj + 0x10) = farPosX;
                *(float*)((uint8_t*)refObj + 0x14) = farPosY;
                *(float*)((uint8_t*)refObj + 0x18) = farPosZ;
                *(uint32_t*)((uint8_t*)refObj + 0x1c) = *(uint32_t*)&cameraVec[3]; // w component?
                *(float*)((uint8_t*)refObj + 0x20) = nearPosX;
                *(float*)((uint8_t*)refObj + 0x24) = nearPosY;
                *(float*)((uint8_t*)refObj + 0x28) = nearPosZ;
                *(uint32_t*)((uint8_t*)refObj + 0x2c) = *(uint32_t*)&cameraVec[3]; // duplicate?
                *(float*)((uint8_t*)refObj + 0x30) = fVar10; // alpha
            }

            // Condition for secondary effect (decal/impact on surface)
            if (slot->pDecalObj == nullptr &&
                spawnIndex > 1 &&
                slot->state == 2 &&
                (this->flags[0] || this->flags[1] || this->flags[2] || this->flags[3])) {
                float normalizedAlpha = (fVar10 - (float)this->someParam2) / (GLOBAL_ONE - (float)this->someParam2);
                if (normalizedAlpha > 0.0f && (GLOBAL_ONE <= normalizedAlpha || normalizedAlpha > 0.0f)) {
                    // Copy camera vector to local matrix
                    float matrixCopy[16];
                    for (int i=0; i<16; i++) matrixCopy[i] = cameraVec[i];
                    // Create secondary effect using same process
                    // Original uses FUN_0044b4e0 on afStack_a0 (cameraVec)
                    // Then virtual call 0x58, then FUN_004df270 for list insertion
                    // We'll stub this as well.
                    // ...
                }
            }

            // Advance indices
            spawnIndex++;
            timelineOffset += 0x28; // 40 bytes per timeline entry
            spawnByteOffset += 0xc0; // 192 bytes per spawn point
            slotIndex++;
        }
    }

private:
    // Members (offsets from this)
    // +0x00: vtable pointer
    // +0x34: float transformMatrix[16] (64 bytes)
    // +0xd8: void* spawnPointArray; (pointer to some object)
    // +0xda: void* timelineArray;
    // +0x1cc-0x1cf: int32_t flags[4];
    // +0x1d0: ImpactSlot slots[4];
    // +0x1e4: int32_t someParam;   // delay?
    // +0x1e5: int32_t someParam2;  // threshold?
    // +0x1e6: int32_t lifetimeMin;
    // +0x1e7: int32_t lifetimeMax;

    // Stub functions (to be filled from other decompilations)
    void* createListNode(uint32_t handle, float* matrixData);
};

// Global vtable reference (from PTR_LAB_00e3a070)
extern void* PTR_LAB_00e3a070;