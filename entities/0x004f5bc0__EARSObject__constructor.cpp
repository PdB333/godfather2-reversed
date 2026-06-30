// FUNC_NAME: EARSObject::constructor
// Address: 0x004f5bc0
// This function appears to be a constructor for an EARS engine object that allocates
// resources from a global pool and creates two handles (position/orientation) from input data.

class EARSObject {
public:
    // Vtable pointer (offset 0x00)
    void** vtable;
    // Unknown fields at offsets: 0x04, 0x08, 0x0C (inferred from offsets)
    int field_0x04;   // +0x04
    int field_0x08;   // +0x08
    int field_0x0C;   // +0x0C
    int* poolSlot;    // +0x10 (offset 0x10) - pointer to something in global pool
    int poolIndex;    // +0x14 (offset 0x14) - index or related
    // +0x18, +0x1C, +0x20 unknown
    int threadSlotA;  // +0x24 (param_1[9]) - thread-local storage slot ID
    int threadSlotB;  // +0x28 (param_1[10]) - second part of thread slot
    int* dataBlock;   // +0x2C (param_1[11]) - pointer to input data (8 ints)
};

// Global data references
extern int* DAT_01206880;          // Pointer to global allocation list head
extern void* PTR_FUN_00e37828;     // Vtable for this class
extern int DAT_00e2b1a4;           // Some global constant (flags?)

// Forward declarations for called functions
void __cdecl FUN_00533cc0();                              // Unknown initialization
struct ThreadSlot* __cdecl FUN_004f7050(int placeholder); // Returns two ints (slot info)
void __cdecl FUN_004f70f0();                              // Deallocate or cleanup
int  __cdecl FUN_004e9270();                              // Create resource handle (returns ID)
void __cdecl FUN_004ebb40();                              // Finalize or register

// Thread-local storage structure (FS segment offset)
struct ThreadLocalData {
    int* threadInfo;    // +0x2C (from FS)
};

EARSObject* __thiscall EARSObject::constructor(EARSObject* this, void* container, int* data) {
    int iVar1;
    uint uVar2;
    int* threadDataPtr;
    int* slotPtr;
    int handle1;
    int* tempSlot;                          // local_10 used as temporary pointer
    int placeholder[3];                     // local_10 array (only first element used as ptr)

    // Base initialization
    FUN_00533cc0();

    // Set vtable
    this->vtable = &PTR_FUN_00e37828;

    // Allocate a thread-local slot (two ints)
    slotPtr = (int*)FUN_004f7050(placeholder);
    iVar1 = *slotPtr;
    this->threadSlotA = iVar1;
    this->threadSlotB = slotPtr[1];

    // Check if this object has already been initialized (flag at container+0x0D)
    if (*(char*)(container + 0x0D) == '\0') {
        // Container says not initialized yet
        if (iVar1 == 0) {
            // Thread slot is zero: we are the first to allocate? Insert into global pool.
            if (this->field_0x04 != 0) {
                // There is an existing pool entry at this->field_0x04
                int* headPtr = (int*)(DAT_01206880 + 0x14);  // +0x14 is pointer to linked list head
                **(void***)headPtr = &PTR_LAB_01123be8;       // Set vtable of old node
                *headPtr = *headPtr + 4;                      // Advance pointer
                *(int*)*headPtr = this->field_0x04;           // Store the old entry
                *headPtr = *headPtr + 4;                      // Advance again
                this->field_0x04 = 0;
                this->poolIndex = 0;
            }
            // Mark container as initialized
            *(char*)(container + 0x0D) = 1;
            return this;
        }
    } else {
        // Container already initialized
        if (iVar1 != 0) {
            // Release the thread slot if it exists
            FUN_004f70f0();
        }
        // If still initialized, return early
        if (*(char*)(container + 0x0D) != '\0') {
            return this;
        }
    }

    // Continue with full initialization
    // Set a bit in container (likely a flag)
    **(uint**)(container + 4) |= 0x80000000;

    int handle2 = DAT_00e2b1a4;                          // Global handle constant
    threadDataPtr = *(int**)(__readfsdword(0x2C));       // Get thread-local storage pointer
    this->dataBlock = data;                              // Store input data pointer

    iVar1 = *threadDataPtr;                              // Get thread-local base
    int* threadBuf = (int*)(*(int*)(iVar1 + 8));         // Buffer from TLS

    // Write first handle info into thread buffer at slot offset
    threadBuf[this->threadSlotA] = 0;                    // +0x00
    threadBuf[this->threadSlotA + 1] = data[0x11];      // +0x04 - note: param_3[0x11] is data["size"]
    threadBuf[this->threadSlotA + 2] = handle2;          // +0x08
    threadBuf[this->threadSlotA + 3] = 0;                // +0x0C

    // Create first handle if any of first four data ints are nonzero (position vector?)
    if (data[0] != 0 || data[1] != 0 || data[2] != 0 || data[3] != 0) {
        placeholder[0] = (int)(threadBuf + this->threadSlotA); // Address in buffer
        handle1 = FUN_004e9270();                              // Create handle
        threadBuf[this->threadSlotA + 4] = handle1;            // Store at +0x10

        uVar2 = threadBuf[this->threadSlotA + 4];
        if (uVar2 != 0 &&
            ((uVar2 != 0xFFFFFFFF && uVar2 < 0x1000) &&
             (uVar2 * 0x38 != -0x11A0F28) &&
             (tempSlot = *(int**)(&DAT_011a0f38 + uVar2 * 0x38), tempSlot != nullptr))) {
            // Increment reference count on handle
            *tempSlot = *tempSlot + 1;
        }
    }

    // Create second handle if next four ints are nonzero (rotation/quaternion?)
    if (data[4] != 0 || data[5] != 0 || data[6] != 0 || data[7] != 0) {
        placeholder[0] = (int)(threadBuf + this->threadSlotA); // Same address
        handle1 = FUN_004e9270();                              // Create second handle
        threadBuf[this->threadSlotA + 5] = handle1;            // Store at +0x14

        uVar2 = threadBuf[this->threadSlotA + 5];
        if (uVar2 != 0 &&
            ((uVar2 != 0xFFFFFFFF && uVar2 < 0x1000) &&
             (uVar2 * 0x38 != -0x11A0F28) &&
             (slotPtr = *(int**)(&DAT_011a0f38 + uVar2 * 0x38), slotPtr != nullptr))) {
            *slotPtr = *slotPtr + 1;
        }
    }

    // Final step
    FUN_004ebb40();
    return this;
}