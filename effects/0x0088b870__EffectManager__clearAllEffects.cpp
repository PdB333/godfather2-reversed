// FUNC_NAME: EffectManager::clearAllEffects

#include <cstdint>

class EffectManager {
public:
    void clearAllEffects();

private:
    // Structure for a dynamically allocated effect node (linked list)
    struct EffectNode {
        Effect* effect;          // +0x00: pointer to actual effect object
        EffectNode* next;        // +0x04
        EffectNode* prev;        // +0x08
    };

    // Structure for an effect object stored in the fixed-size pool
    struct Effect {
        // AABB data
        float minX;              // +0x30
        float minY;              // +0x34
        float minZ;              // +0x38
        float maxX;              // +0x40
        float maxY;              // +0x44
        float maxZ;              // +0x48
        uint32_t flags;          // +0x54 (bit 8 = some flag, e.g., kEffectFlag_NoAABB)
        // ... other data (size 0x50 total)
    };

    // Pool of preallocated effects (size 0x50 each)
    Effect* poolStart;           // +0x7C
    Effect* poolEnd;             // +0x80

    // Linked list of active dynamic effects
    EffectNode* head;            // +0x1C4
    EffectNode* tail;            // +0x1C8
    int32_t nodeCount;           // +0x1CC

    // VTable for node allocator/destructor
    void** nodeAllocatorVTable;  // +0x1D4 (points to an object with vtable at +4)

    // Other members
    uint32_t unknown_0x260;      // +0x260 (cleared)
    void* somePointer_0x25C;     // +0x25C (released via FUN_009c8f10)
    uint32_t unknown_0x264;      // +0x264 (cleared)
};

void EffectManager::clearAllEffects()
{
    // 1. Clear the fixed-size pool: zero out the "used" flag at offset +0x0C for each effect
    int numPoolEffects = (poolEnd - poolStart);  // size of pool in bytes? Actually pointer difference is in bytes
    // But the loop divides by 0x50 (sizeof(Effect)), so poolStart/poolEnd are Effect*
    int count = (poolEnd - poolStart); // since pointers are to Effects, difference is number of effects
    // Note: The decompiled code uses raw pointer arithmetic, so poolStart/End are char*? We'll treat as Effect*.

    // The original loop is do-while; reconstruct as for-loop to avoid off-by-one with count=0
    for (int i = 0; i < count; i++) {
        // Zero out the field at offset 0x0C (might be a usage flag or reference count)
        int* field = reinterpret_cast<int*>(reinterpret_cast<char*>(poolStart) + i * 0x50 + 0x0C);
        *field = 0;
    }

    // 2. Destroy all dynamically allocated effect nodes
    while (head != nullptr) {
        EffectNode* node = head;

        // Extract the effect pointer stored at offset 0 of the node
        Effect* effect = node->effect; // Actually node->effect is stored at offset 0, but the code uses *piVar1 (first field)
        // The code assigned iVar3 = *piVar1; so iVar3 is the effect pointer. We'll adjust.

        // Remove node from linked list
        if (node == tail) {
            tail = nullptr;
            head = nullptr;
        } else {
            head = node->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }

        // Call node destructor via the node allocator's vtable
        // The vtable is at (**nodeAllocatorVTable)[1] (offset 4)
        void (*destroyNode)(EffectNode*, int) = reinterpret_cast<void (*)(EffectNode*, int)>(
            (*reinterpret_cast<void***>(nodeAllocatorVTable))[1]
        );
        destroyNode(node, 0);

        nodeCount--;

        // Access the effect's AABB and flags
        // The effect has a sub-structure at offset +0x14 that holds the AABB
        // Actually code: iVar2 = *(int *)(iVar3 + 0x14); then uses floats at +0x30, etc.
        // So effect->someSubStruct points to a struct with AABB
        // We'll assume Effect has a member at +0x14 that is a pointer to AABBData
        struct AABBData {
            float minX;   // +0x30
            float minY;   // +0x34
            float minZ;   // +0x38
            float maxX;   // +0x40
            float maxY;   // +0x44
            float maxZ;   // +0x48
            uint32_t flags2; // +0x54 (bit 8 = kAABBFlag_XXX)
        };
        // Actually the offsets are from iVar2, so we need to add base offset of effect to get to AABB
        // Since iVar2 = effect + 0x14, the AABB floats are at iVar2 + 0x30, etc.
        // So relative to effect: AABB at offset 0x14 + 0x30 = 0x44? That seems off. Let's recalc.
        // Original: iVar2 = *(int *)(iVar3 + 0x14); Then checks *(float *)(iVar2 + 0x30) etc.
        // So iVar3 is effect pointer, iVar2 is some other pointer stored at effect+0x14.
        // That pointer points to a structure with floats at offsets 0x30,0x34,0x38,0x40,0x44,0x48 and flag at 0x54.
        // So the AABB is not directly part of effect; it's another object.
        // We'll call it AABBData.
        AABBData* aabb = reinterpret_cast<AABBData*>(effect->aabbPtr); // Assume effect has a member at +0x14

        // Check if AABB is valid (min < max) and flag bit 8 not set
        bool aabbValid = (aabb->minX < aabb->maxX || aabb->minX == aabb->maxX) &&
                         (aabb->minY < aabb->maxY || aabb->minY == aabb->maxY) &&
                         (aabb->minZ < aabb->maxZ || aabb->minZ == aabb->maxZ);
        bool flagClear = (aabb->flags2 & 0x8) == 0;

        if (aabbValid && flagClear) {
            // Call some function with the effect pointer stored at node+0x08? Actually node->effect is at 0, but the code uses *(int *)(iVar3 + 8)
            // That is different: it accesses effect at offset 0? Wait: the call is FUN_00429460(*(undefined4 *)(iVar3 + 8));
            // So iVar3 was the effect pointer (from node->effect), and then it uses offset +8 from that.
            // That suggests the effect object has another pointer at +0x08.
            // Since the effect is of size 0x50, offset +0x08 might be a handle or reference.
            // We'll call it effect->someHandle (at +0x08).
            // And FUN_00429460 probably removes it from a spatial container.
            void* handle = reinterpret_cast<void*>(effect->someHandle); // Assume at +0x08
            FUN_00429460(handle);
        }

        // Call FUN_0088af60 to finalize this effect object
        // Parameters: effect pointer, 1, 0
        FUN_0088af60(effect, 1, 0);
    }

    // Clear remaining fields
    unknown_0x260 = 0;
    FUN_009c8f10(somePointer_0x25C);
    somePointer_0x25C = nullptr;
    unknown_0x264 = 0;
}