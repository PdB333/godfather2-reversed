// FUNC_NAME: PerThreadData::getInstance
// Address: 0x004e9fa0
// Role: Thread-local singleton getter for a per-thread context block (size 0x134 bytes)
// Uses Windows TLS via FS segment offset 0x2c (ThreadLocalStoragePointer). Allocates and initializes on first call.

class PerThreadData {
public:
    uint32_t unk0;          // offset 0x00 - initialized to 0
    uint32_t unk4;          // offset 0x04 - initialized to 0
    uint32_t unk8;          // offset 0x08 - initialized to 0xFFFFFFFF (-1)
    uint8_t pad9C[0x9C - 0x0C]; // padding to reach offset 0x9C
    uint32_t unk9C;         // offset 0x9C - initialized to 0
    uint32_t unkA0;         // offset 0xA0 - initialized to 0xFFFFFFFF (-1)
    // Total size 0xA4? But allocation is 0x134, so there are more fields.
    uint8_t padding[0x134 - 0xA4]; // remainder
};

// Static method to retrieve the thread-local instance
static PerThreadData* PerThreadData::getInstance() {
    // Access the TLS array via FS:[0x2c] (ThreadLocalStoragePointer)
    // iVar1 = *(*((uint32_t*)__readfsdword(0x2c))) - double indirection yields current TLS slot value?
    // For clarity, we assume a typical pattern: read TLS slot at index (0x2c/4) = 0x0B? But the code does:
    // iVar1 = **(int **)(FS + 0x2c); then check iVar1[0x2c/4]? Actually the decompile shows:
    // iVar1 = **(int **)(unaff_FS_OFFSET + 0x2c);   // get pointer to TLS array, then first entry?
    // if (*(int *)(iVar1 + 0x2c) == 0)  // check an offset 0x2c within that?
    // Given the ambiguity, we implement the observed allocation logic.

    uint32_t* tlsArray = *(uint32_t**)__readfsdword(0x2c); // Get TLS array base
    uint32_t* slotPtr = tlsArray + (0x2c / 4); // Actually, the code uses iVar1 + 0x2c directly, so treat iVar1 as base pointer of a per-thread structure
    // Alternatively, the code might be using a custom TLS where the first pointer is a structure containing a slot at offset 0x2c.
    // We'll mimic the logic: if the value at that slot is null, allocate and store.

    if (*slotPtr == 0) {
        // Allocate 0x134 bytes using custom allocator (FUN_009c8ed0) with parameters (2, 0x10, 0)
        PerThreadData* instance = (PerThreadData*)FUN_009c8ed0(0x134, (uint32_t[]){2, 0x10, 0});
        if (instance != nullptr) {
            instance->unk4 = 0;
            instance->unk8 = 0xFFFFFFFF;
            instance->unk9C = 0;
            instance->unkA0 = 0xFFFFFFFF;
            // Store pointer into the TLS slot
            *slotPtr = (uint32_t)instance;
            instance->unk0 = 0;
            return instance;
        }
        *slotPtr = 0;
    }
    return (PerThreadData*)(*slotPtr);
}