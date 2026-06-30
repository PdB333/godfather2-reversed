// FUNC_NAME: ShaderEffect::ShaderEffect
// Address: 0x004f5bc0
// Role: Constructor for ShaderEffect class - initializes shader resource handles from a parameter block.
// Uses EA EARS engine resource management with freelist recycling and reference counting.

#include <cstdint>

// Forward declarations for known engine functions and globals
void __cdecl baseConstructor(); // FUN_00533cc0 - base class constructor
int* __cdecl allocateMemory(int* outInfo); // FUN_004f7050 - returns pointer to allocated block info
void __cdecl freeMemory(); // FUN_004f70f0 - frees memory
void __cdecl referenceResource(uint32_t resourceHandle); // FUN_004e9270 - increments reference count
void __cdecl finalizeInit(); // FUN_004ebb40 - final initialization step

// External globals
extern uint32_t DAT_01206880; // pointer to freelist head pointer (offset +0x14)
extern uint32_t DAT_00e2b1a4; // default resource handle or constant

// This structure represents the ShaderEffect object layout (based on offsets)
class ShaderEffect {
public:
    void** vtable;           // +0x00
    uint32_t field_4;        // +0x04
    uint32_t field_8;        // +0x08
    uint32_t field_C;        // +0x0C
    void* oldResource;       // +0x10 (field_4 in original code)
    void* oldResource2;      // +0x14 (field_5)
    uint32_t field_18;       // +0x18
    uint32_t field_1C;       // +0x1C
    uint32_t field_20;       // +0x20
    int* allocPointer;       // +0x24 (offset 9) - pointer to allocated memory
    int   allocSize;         // +0x28 (offset 10) - size of allocated memory
    void* parameterBlock;    // +0x2C (offset 11) - saved parameter block pointer
};

// Parameter block descriptor passed as param_3
struct ShaderParameterBlock {
    float values[12];       // indices 0-11
    uint32_t textureHandle0; // index 0x10? (actually param_3[0x11] used)
    // layout assumed: first 4 floats, next 4 floats, then some padding, then a handle at offset 0x44 (0x11*4)
};

// Resource descriptor passed as param_2 (assumed structure)
struct ResourceDescriptor {
    uint32_t flagsPtr;      // +0x00 - pointer to flags
    uint8_t reuseFlag;      // +0x0D - reuse flag
    // other fields unknown
};

// Constructor
ShaderEffect* __thiscall ShaderEffect::ShaderEffect(ShaderEffect* thisPtr, ResourceDescriptor* desc, ShaderParameterBlock* params) {
    // base constructor call
    baseConstructor();

    // Set vtable pointer (class-specific)
    thisPtr->vtable = &PTR_FUN_00e37828;  // external vtable pointer symbol

    // Clear allocation info
    thisPtr->allocPointer = nullptr;
    thisPtr->allocSize = 0;

    // Allocate memory for internal resources; returns info into local_10
    int allocInfo[3]; // local_10
    int* allocResult = allocateMemory(allocInfo);
    int allocPtr = allocResult[0];
    int allocLen = allocResult[1];
    thisPtr->allocPointer = (int*)allocPtr;
    thisPtr->allocSize = allocLen;

    // Check reuse flag at desc->reuseFlag
    if (desc->reuseFlag == 0) {
        if (allocPtr == 0) {
            // Attempt to recycle old resource if present
            if (thisPtr->oldResource != nullptr) {
                // Get freelist head pointer from global +0x14
                int** freelistHead = (int**)(DAT_01206880 + 0x14);
                // Point old resource to freelist vtable
                **freelistHead = &PTR_LAB_01123be8;  // external vtable for freed objects
                *freelistHead = *freelistHead + 4;    // advance pointer
                **freelistHead = (int)thisPtr->oldResource;  // store old resource address
                *freelistHead = *freelistHead + 4;
                // Clear old resource references
                thisPtr->oldResource = nullptr;
                thisPtr->oldResource2 = nullptr;
            }
            desc->reuseFlag = 1;
            return thisPtr;
        }
    } else {
        if (allocPtr != 0) {
            freeMemory(); // free the allocated memory
        }
        if (desc->reuseFlag != 0) {
            return thisPtr; // already reused, nothing to do
        }
    }

    // Mark descriptor as in use (set high bit on flags pointer)
    *(uint32_t*)(desc->flagsPtr) |= 0x80000000;

    // Save parameter block pointer
    thisPtr->parameterBlock = (void*)params;

    // Get thread-local storage for temporary buffer
    // unaff_FS_OFFSET + 0x2c points to some thread-local structure
    int* tlsBase = *(int**)(__readfsdword(0x2c)); // FS segment offset 0x2c
    int tlsVar1 = *tlsBase; // some base pointer

    // Write shader resource data into temporary buffer at offset allocPointer
    int* buffer = (int*)(*(int*)(tlsVar1 + 8) + (int)thisPtr->allocPointer);
    buffer[0] = 0;                    // +0x00
    buffer[1] = params->textureHandle0;  // from param_3[0x11]
    buffer[2] = DAT_00e2b1a4;        // default handle
    buffer[3] = 0;                    // padding

    // Handle first 4 floats if non-zero
    if (params->values[0] != 0 || params->values[1] != 0 || params->values[2] != 0 || params->values[3] != 0) {
        allocInfo[0] = (int)buffer;
        uint32_t resourceHandle = referenceResource((uint32_t)buffer + 0x10); // creates reference at offset 0x10
        buffer[0x10/4] = resourceHandle; // store handle at offset 0x10
        uint32_t handle = buffer[0x10/4];
        if (handle != 0 && handle != 0xFFFFFFFF && handle < 0x1000) {
            // Access global resource table at DAT_011a0f38 + handle*0x38
            int* refCount = *(int**)(&DAT_011a0f38 + handle * 0x38);
            if (refCount != nullptr) {
                *refCount += 1; // increment reference count
            }
        }
    }

    // Handle second 4 floats (indices 4-7)
    if (params->values[4] != 0 || params->values[5] != 0 || params->values[6] != 0 || params->values[7] != 0) {
        allocInfo[0] = (int)buffer;
        uint32_t resourceHandle2 = referenceResource((uint32_t)buffer + 0x14);
        buffer[0x14/4] = resourceHandle2;
        uint32_t handle2 = buffer[0x14/4];
        if (handle2 != 0 && handle2 != 0xFFFFFFFF && handle2 < 0x1000) {
            int* refCount2 = *(int**)(&DAT_011a0f38 + handle2 * 0x38);
            if (refCount2 != nullptr) {
                *refCount2 += 1;
            }
        }
    }

    // Final initialization step
    finalizeInit();

    return thisPtr;
}