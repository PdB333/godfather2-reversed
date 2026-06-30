// FUNC_NAME: cleanupAllocationBlocks
void cleanupAllocationBlocks(int unusedParam, void* inputData) {
    // Stack buffer for first descriptor block (384 bytes, holds 8 descriptors of 0x30 each)
    char buffer1[384];
    // Stack buffer for second descriptor block (396 bytes)
    char buffer2[396];

    // Descriptor pointers and metadata
    void** allocatorPtr1 = &PTR_LAB_00e397fc;  // global allocator pointer
    uint32_t allocatorData1 = DAT_00e445dc;    // allocator data
    char* desc1Ptr = buffer1;
    uint32_t desc1Flags = 0x80000008;           // flag: top bit set means "not to be freed"

    void** allocatorPtr2 = &PTR_LAB_00e397fc;
    uint32_t allocatorData2 = DAT_00e445dc;
    char* desc2Ptr = buffer2;
    uint32_t desc2Flags = 0x80000008;

    // Temporary unknown fields (set to 0)
    uint32_t unknown1 = 0;
    uint32_t unknown2 = 0;

    // Set up the descriptor structures on stack (size matches layout expected by next call)
    // The structure is defined as:
    // struct DescriptorBlock {
    //     void** allocator;   // +0x00
    //     uint32_t allocData; // +0x04
    //     char* buffer;       // +0x08
    //     uint32_t flags;     // +0x0C
    //     uint32_t reserved;  // +0x10
    // } // total 0x14 bytes
    // Then the block holds multiple descriptors (count from flags low bits)

    // Call function to initialize descriptor blocks from inputData
    initializeDescriptorBlocks(inputData, &allocatorPtr2);  // actually passes pointer to descriptor struct

    // Reset allocator pointer for second check
    allocatorPtr2 = &PTR_LAB_00e397fc;

    // Check if first descriptor block should be freed (flags >= 0 means freeable)
    if ((int)desc1Flags >= 0) {
        uint32_t descriptorCount = desc1Flags & 0x3FFFFFFF;
        void* tlsValue = TlsGetValue(DAT_01139810);
        deallocateMemoryBlock(desc1Ptr, descriptorCount * 0x30, 0x17);  // 0x17 = pool magic
    }

    // Reset allocator pointer again
    allocatorPtr2 = &PTR_LAB_00e397fc;

    // Check second descriptor block
    if ((int)desc2Flags >= 0) {
        uint32_t descriptorCount = desc2Flags & 0x3FFFFFFF;
        void* tlsValue = TlsGetValue(DAT_01139810);
        deallocateMemoryBlock(desc2Ptr, descriptorCount * 0x30, 0x17);
    }
}