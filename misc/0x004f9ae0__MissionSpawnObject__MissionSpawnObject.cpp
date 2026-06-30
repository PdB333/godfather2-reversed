// FUNC_NAME: MissionSpawnObject::MissionSpawnObject

#include <cstdint>

// Forward declarations for called functions
int* __stdcall getScreenExtents(int* out);
void __cdecl updatePendingOperations();
void __cdecl computeFrameTime();
void __cdecl processDeferredOperations();
bool __thiscall validatePosition(void* unk, int offset);
void __thiscall processSpawnIndex(int index);
void* __thiscall getHandler(int* flags);
int __thiscall allocateEventBatch(void* owner, int param2, int param3, void* param4);
void __thiscall stringFromTransform(void* transformArray, void* buffer);
uint32_t __fastcall hashString(uint32_t seed, void* str, int len);

class MissionSpawnObject {
public:
    // Vtable pointer at +0x00
    virtual ~MissionSpawnObject();

    // Offsets based on decompile
    // +0x04: uint32_t* mObjectData (connected to global pool)
    // +0x08: 
    // +0x0C: 
    // +0x10: float mSpawnPosX (or offset from something)
    // +0x11: float mSpawnPosY
    // +0x14: 
    // +0x15: 
    // +0x16: 
    // +0x17-0x1D: float mDefaultParams[7] (initialized to 0.5f)
    // +0x1E: 
    // +0x1F: 
    // +0x20: 
    // +0x22: 
    // +0x24: 
    // +0x25: 
    // +0x26: 
    // +0x27-0x3B: float mThingMatrix[16] (4x4)
    // +0x3C: 
    // +0x3D: 
    // +0x3E: 
    // +0x3F: 
    // +0x40: 
    // +0x41: 
    // +0x42: 
    // +0x43: 
    // +0x44: float mCompositeParam1 (0x4C offset)
    // +0x45: float mCompositeParam2
    // +0x46: float mCompositeParam3
    // +0x47: float mCompositeParam4
    // +0x48: float mCompositeParam5
    // +0x49: float mCompositeParam6
    // +0x4A: float mCompositeParam7
    // +0x4B: 
    // +0x4C: 0x3f000000 (0.5f)
    // +0x4D: 0x3f000000
    // +0x4E: 0x3f000000
    // +0x4F: 0x3f000000
    // +0x50: 0x3f000000
    // +0x51: 0x3f000000
    // +0x52: 0x3f000000
    // +0x53: 
    // +0x54: uint32_t mFlag1 (compared to 2)
    // +0x55: 
    // +0x56: uint32_t mFlag2 (compared to 2)
    // +0x57: 
    // +0x58: int mCounterA (zeroed)
    // +0x59: int mCounterB (zeroed)
    // +0x5A: int mCounterC (zeroed)
    // +0x5B: int mAssetHandle (spawned object ID)
    // +0x5C: 
    // ... more fields

    // Constructor
    MissionSpawnObject(void* gameState, uint32_t* definition);

    // Internal data
    // Other fields as per offsets above
    uint32_t* mObjectData;      // +0x04
    uint32_t mField08;          // +0x08
    uint32_t mField0C;          // +0x0C
    uint32_t* mDefinition;      // +0x0F (param_3 stored)
    // ... plus many others
};

// Global data references (from decompile)
extern void* PTR_FUN_00e37a58;                // vtable
extern uint32_t DAT_01206880;                  // global pool offset
extern void* LAB_01123be8;                     // some label
extern float DAT_00e2b1a4;                     // default float (maybe 0.5)
extern float DAT_00e445c8;                     // multiplier
extern uint32_t DAT_01205510;                  // collision/validation context
extern uint32_t DAT_01205968;                  // hash table base
extern uint32_t DAT_011a0f38;                  // reference count base
extern float PTR_DAT_00e2dba4;                // matrix data source
extern float PTR_DAT_00e2dbd8;
extern float PTR_DAT_00e2dbdc;
extern float PTR_DAT_00e2dba0;

// Constructor implementation
MissionSpawnObject::MissionSpawnObject(void* gameState, uint32_t* definition)
{
    // Base initialization (likely parent class constructor)
    updatePendingOperations();

    // Set vtable
    *(void**)this = &PTR_FUN_00e37a58;

    // Initialize screen position
    {
        int temp[2];
        int* result = getScreenExtents(temp);
        this->mField10 = result[0];
        this->mField11 = result[1];
    }

    // Check if already initialized
    if (*(char*)((uint8_t*)gameState + 0x0D) == 0) {
        // Not loaded/initialized yet
        if (this->mObjectData == 0) {
            // Already null, proceed
        } else {
            // Move object data to global pool
            int** poolPtr = (int**)(DAT_01206880 + 0x14);
            **(int***)poolPtr = &LAB_01123be8;
            *poolPtr = *poolPtr + 4;
            **(int**)poolPtr = (int)this->mObjectData;
            *poolPtr = *poolPtr + 4;
            this->mObjectData = 0;
            // Also clear next word (mField05 assumed)
            *(uint32_t*)((uint8_t*)this + 0x14) = 0;
        }
        *(char*)((uint8_t*)gameState + 0x0D) = 1;
        return; // Early return
    } else {
        // Already loaded/initialized
        if (this->mField10 != 0) {
            computeFrameTime(); // Likely cleanup
        }
        if (*(char*)((uint8_t*)gameState + 0x0D) != 0) {
            return; // Already done
        }
    }

    // Mark gameState as invalid
    **(uint32_t**)((uint8_t*)gameState + 4) |= 0x80000000;

    // Get thread-local offset (per-frame variable)
    int* perFrameVar = *(int**)(*(int*)(__readfsdword(0x2C)) + 8);
    int frameOffset = *perFrameVar;

    // Store definition pointer
    ((uint32_t*)this)[0x0F] = (uint32_t)definition;

    // Copy position with optional additive mode
    uint32_t* destPos = (uint32_t*)((uint32_t)this->mObjectData + 0x40 + frameOffset);
    if ((definition[0x14] & 0x40) == 0) {
        destPos[0] = definition[0x24]; // x
        destPos[1] = definition[0x25]; // y
        destPos[2] = definition[0x26]; // z
    } else {
        destPos[0] = definition[0x24] + destPos[0]; // additive x
        destPos[1] = definition[0x25] + destPos[1]; // additive y
        destPos[2] = definition[0x26] + destPos[2]; // additive z
    }

    // Perform additional initialization
    processDeferredOperations();
    processDeferredOperations(); // Called twice
    processDeferredOperations();

    // Clear flags in definition based on this object's flags
    if (*(uint32_t*)((uint8_t*)this + 0x54) != 2) {
        definition[0x14] &= 0xFFFFFFFE; // Clear bit 0
    }
    if (*(uint32_t*)((uint8_t*)this + 0x56) != 2) {
        definition[0x14] &= 0xFFFFFFFD; // Clear bit 1
    }

    // Store some value from definition
    ((uint32_t*)this)[0x0E] = definition[0x22];

    // Handle speed/scaling factor
    float defaultVal = DAT_00e2b1a4;
    if ((float)definition[0x15] == 0.0f) {
        ((float*)this)[0x12] = defaultVal;
    } else {
        double scaled = (double)((float)definition[0x15] * DAT_00e445c8);
        computeFrameTime(); // Random? maybe noise
        ((float*)this)[0x12] = (float)scaled;
    }

    // Zero counters
    ((uint32_t*)this)[0x58] = 0;
    ((uint32_t*)this)[0x59] = 0;
    ((uint32_t*)this)[0x5A] = 0;

    // Initialize 7 float fields with default value
    float* defaultArray = (float*)((uint32_t*)this + 0x17);
    for (int i = 0; i < 7; i++) {
        defaultArray[i] = defaultVal;
    }

    // Initialize matrix (16 floats starting at offset 0x31*4 = 0xC4)
    uint32_t* mat = (uint32_t*)((uint8_t*)this + 0xC4); // offset 0x31
    if ((float)definition[0x11] == 0.0f) {
        // Copy from default pattern
        for (int i = 0; i < 16; i += 4) {
            mat[i+0] = *(uint32_t*)&PTR_DAT_00e2dba4[i];   // Actually careful: the original loops copy 2x2 blocks
        }
        // Reconstructed as per original loop:
        uint32_t* src = (uint32_t*)&PTR_DAT_00e2dba4;
        for (int i = 0; i < 16; i += 4) {
            mat[i-1] = src[i-1];
            mat[i]   = src[i];
            mat[i+1] = src[i-1];
            mat[i+2] = src[i];
        }
    } else {
        // Identity-like pattern from other sources
        uint32_t* src1 = (uint32_t*)&PTR_DAT_00e2dbd8;
        uint32_t* src2 = (uint32_t*)&PTR_DAT_00e2dbdc;
        uint32_t* src3 = (uint32_t*)&PTR_DAT_00e2dba0;
        uint32_t* src4 = (uint32_t*)&PTR_DAT_00e2dba4;
        for (int i = 0; i < 56; i += 8) {
            mat[i-1] = src1[i];
            mat[i]   = src2[i];
            mat[i+1] = src3[i];
            mat[i+2] = src4[i];
        }
    }

    // Initialize composite parameters (7 floats at 0x4C)
    ((float*)this)[0x4C] = 0.5f;
    ((float*)this)[0x4D] = 0.5f;
    ((float*)this)[0x4E] = 0.5f;
    ((float*)this)[0x4F] = 0.5f;
    ((float*)this)[0x50] = 0.5f;
    ((float*)this)[0x51] = 0.5f;
    ((float*)this)[0x52] = 0.5f;

    // Copy 4 floats from object data to local then to this fields
    uint32_t* srcPos = (uint32_t*)((uint32_t)this->mObjectData + 0x80 + frameOffset);
    uint32_t temp[4];
    temp[0] = srcPos[0];
    temp[1] = srcPos[1];
    temp[2] = srcPos[2];
    temp[3] = srcPos[3];

    // Set fields from definition
    ((uint32_t*)this)[0x0A] = definition[0];
    ((uint32_t*)this)[0x0B] = definition[1];
    ((uint32_t*)this)[0x0D] = ((uint32_t*)this)[1]; // from this+0x04
    ((uint32_t*)this)[0x0C] = definition[2];

    // Validate position
    if (!validatePosition((void*)DAT_01205510, frameOffset + (int)((uint32_t*)this)[0x10])) {
        *(char*)((uint8_t*)gameState + 0x0C) = 1;
        return;
    }

    // Process spawn indices
    int* basePtr = *(int**)perFrameVar;
    int count = *(int*)((uint8_t*)basePtr + 0x58 + (int)((uint32_t*)this)[0x10]);
    for (int i = 0; i < count; i++) {
        int index = *(int*)((uint8_t*)basePtr + 8 + i * 8 + (int)((uint32_t*)this)[0x10]);
        if (index != 0) {
            int* objPtr = (int*)((uint8_t*)basePtr + index);
            int spawnIdx = objPtr[0x10]; // +0x40
            if (spawnIdx < 1) {
                spawnIdx = definition[0x23];
            } else {
                float checkVal = *(float*)(*(int*)((uint8_t*)objPtr + 0x24) + 0x3C);
                if (checkVal == DAT_00e2b1a4) {
                    continue; // skip
                }
            }
            if (spawnIdx > 0) {
                processSpawnIndex(spawnIdx);
            }
        }
    }

    // Handle 4x4 matrix from definition offset 4..7
    uint32_t* matDef = &definition[4];
    if (matDef[0] == 0 && matDef[1] == 0 && matDef[2] == 0 && matDef[3] == 0) {
        ((uint32_t*)this)[0x5B] = 0;
    } else {
        // Get owner from this+0x04
        uint32_t owner = *(uint32_t*)((uint8_t*)this + 4); // mField04?
        int localVal = 0;
        if (matDef[0] == 0 && matDef[1] == 0 && matDef[2] == 0 && matDef[3] == 0) {
            ((uint32_t*)this)[0x5B] = 0;
        } else {
            int* flags = (int*)getHandler(&localVal);
            int result = 0;
            if (flags != 0 && *flags != 0) {
                void* batch = allocateEventBatch(definition, owner, 0, &localVal, nullptr);
                result = (int)batch;
            }
            ((uint32_t*)this)[0x5B] = result;
        }
        if (((uint32_t*)this)[0x5B] != 0) {
            *(uint32_t**)(((uint32_t*)this)[0x5B] + 8) = (uint32_t*)this + 0x5B;
        }
    }

    // Handle definition matrix 8..11
    uint32_t* matDef2 = &definition[8];
    if (matDef2[0] != 0 || matDef2[1] != 0 || matDef2[2] != 0 || matDef2[3] != 0) {
        uint32_t hashResult;
        if (matDef2[0] == 0 && matDef2[1] == 0 && matDef2[2] == 0 && matDef2[3] == 0) {
            hashResult = 0;
        } else {
            char buffer[64];
            stringFromTransform(matDef2, buffer);
            int len = 0;
            while (buffer[len] != 0) len++;
            uint32_t hash = hashString(0, buffer, len);
            uint32_t* bucket = *(uint32_t**)(*(int*)(DAT_01205968 + 0x80C) + (hash % *(uint32_t*)(DAT_01205968 + 0x808)) * 4);
            if (bucket == nullptr) {
                hashResult = 0xFFFFFFFF;
            } else {
                while (true) {
                    if (bucket[0] == hash) {
                        if (bucket[1] == 0) {
                            hashResult = 0xFFFFFFFF;
                        } else {
                            hashResult = *(uint32_t*)bucket[1];
                        }
                        break;
                    }
                    bucket = (uint32_t*)bucket[2];
                    if (bucket == nullptr) {
                        hashResult = 0xFFFFFFFF;
                        break;
                    }
                }
            }
        }
        // Store result in per-frame state
        *(uint32_t*)(*perFrameVar + 0xAC + (int)((uint32_t*)this)[0x10]) = hashResult;
        uint32_t refIdx = *(uint32_t*)(*perFrameVar + 0xAC + (int)((uint32_t*)this)[0x10]);
        if (refIdx != 0 && refIdx != 0xFFFFFFFF && refIdx < 0x1000) {
            int offset = refIdx * 0x38;
            if (offset != -0x11A0F28) {
                int* refCount = *(int**)((uint8_t*)&DAT_011a0f38 + offset);
                if (refCount != 0) {
                    *refCount = *refCount + 1;
                }
            }
        }
    }

    // Handle definition matrix 12..15 (similar)
    uint32_t* matDef3 = &definition[0x0C];
    if (matDef3[0] != 0 || matDef3[1] != 0 || matDef3[2] != 0 || matDef3[3] != 0) {
        uint32_t hashResult;
        if (matDef3[0] == 0 && matDef3[1] == 0 && matDef3[2] == 0 && matDef3[3] == 0) {
            hashResult = 0;
        } else {
            char buffer[64];
            stringFromTransform(matDef3, buffer);
            int len = 0;
            while (buffer[len] != 0) len++;
            uint32_t hash = hashString(0, buffer, len);
            uint32_t* bucket = *(uint32_t**)(*(int*)(DAT_01205968 + 0x80C) + (hash % *(uint32_t*)(DAT_01205968 + 0x808)) * 4);
            if (bucket == nullptr) {
                hashResult = 0xFFFFFFFF;
            } else {
                while (true) {
                    if (bucket[0] == hash) {
                        if (bucket[1] == 0) {
                            hashResult = 0xFFFFFFFF;
                        } else {
                            hashResult = *(uint32_t*)bucket[1];
                        }
                        break;
                    }
                    bucket = (uint32_t*)bucket[2];
                    if (bucket == nullptr) {
                        hashResult = 0xFFFFFFFF;
                        break;
                    }
                }
            }
        }
        *(uint32_t*)(*perFrameVar + 0xB0 + (int)((uint32_t*)this)[0x10]) = hashResult;
        uint32_t refIdx = *(uint32_t*)(*perFrameVar + 0xB0 + (int)((uint32_t*)this)[0x10]);
        if (refIdx != 0 && refIdx != 0xFFFFFFFF && refIdx < 0x1000) {
            int offset = refIdx * 0x38;
            if (offset != -0x11A0F28) {
                int* refCount = *(int**)((uint8_t*)&DAT_011a0f38 + offset);
                if (refCount != 0) {
                    *refCount = *refCount + 1;
                }
            }
        }
    }

    // Return this
}