// FUN_004c6aa0: InternalContainer::releaseAll

class InternalContainer {
public:
    void releaseAll();

private:
    // Offset 0x00
    uint32_t field_0;
    // Offset 0x04
    uint32_t field_4;
    // Offset 0x08
    uint32_t field_8;

    // Offsets 0x24 (0x90) and 0x25 (0x94)
    uint32_t field_90;
    uint32_t field_94;

    // Offset 0x26 (0x98) - count of items in first array
    uint32_t arrayCount;
    // Offset 0x27 (0x9C) - pointer to first dynamic array
    void* arrayPtr;

    // Offset 0x28 (0xA0) - secondary count or flag for second pointer
    uint32_t field_A0;
    // Offset 0x29 (0xA4) - pointer to second dynamic object
    void* singlePtr;

    // Offset 0x2A (0xA8)
    uint32_t field_A8;
};

// External helper functions
extern void FUN_0060bad0();   // Release a single element from the array
extern void FUN_009c8f10(void* ptr); // Free an allocated block

void InternalContainer::releaseAll() {
    // Release first dynamic array if present
    if (arrayPtr != nullptr && arrayCount != 0) {
        for (uint32_t i = 0; i < arrayCount; ++i) {
            FUN_0060bad0(); // Release element (called twice per slot?)
            FUN_0060bad0();
        }
        FUN_009c8f10(arrayPtr); // Free the array memory
        arrayPtr = nullptr;
        arrayCount = 0;
    }

    // Release second single pointer if present
    if (singlePtr != nullptr) {
        FUN_009c8f10(singlePtr);
        singlePtr = nullptr;
        field_A0 = 0;
    }

    // Zero out all other fields
    field_4 = 0;
    field_8 = 0;
    field_90 = 0;
    field_94 = 0;
    field_0 = 0;
    field_A8 = 0;
}