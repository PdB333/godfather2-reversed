// FUNC_NAME: MemoryPoolNode::initializeFromBlock
void MemoryPoolNode::initializeFromBlock(void* param_2, void* blockPtr)
{
    // blockPtr: pointer to a source memory block (unaff_EDI)
    // param_2: some external value (likely a user pointer)

    uint32_t blockFlags = *(uint32_t*)((char*)blockPtr + 4);           // +0x04: flags/size
    uint32_t sizeMasked = blockFlags & 0x7ffffff8;                     // lower 3 bits and top bit cleared
    uint32_t flagWord = *(uint32_t*)((char*)blockPtr + sizeMasked + 4); // read flag word at offset from block

    // Store the external value into this node
    *this->userPtr = param_2;

    if ((flagWord & 1) == 0) {
        // Case A: flag not set, small/constant allocation
        this->size = sizeMasked;                                // +0x08
        this->flagsLow = 4;                                     // +0x14
        this->sourceBlock = blockPtr;                           // +0x04
        this->metadataPtr = (uint32_t*)((char*)blockPtr + 4);   // +0x0C
        this->dataSize = sizeMasked - 0x10;                     // +0x10
        this->flagsHigh = 0;                                    // +0x15
    } else {
        // flagWord bit0 set -> allocation needed from external allocator
        void* allocated = FUN_00647c90(); // external memory allocator

        this->sourceBlock = blockPtr;                         // +0x04

        // Compute low flags: if (blockFlags & 4) -> value 0x10 else 2
        uint32_t cond = (blockFlags & 4) ? (uint32_t)-1 : 0;
        this->flagsLow = (cond & 0xe) + 2;                    // +0x14

        if (blockFlags & 2) {
            // Case B1: extra offset from block base
            this->size = *(uint32_t*)blockPtr + 0x10 + sizeMasked;  // +0x08
            this->metadataPtr = (uint32_t*)((char*)blockPtr + 8);   // +0x0C (blockPtr + 2*4)
            this->dataPtr = allocated;                      // +0x10
            this->flagsHigh = 1;                            // +0x15
        } else {
            // Case B2: no extra offset
            this->size = sizeMasked;                        // +0x08
            this->metadataPtr = (uint32_t*)((char*)blockPtr + 8);   // +0x0C
            this->dataPtr = allocated;                      // +0x10
            this->flagsHigh = 0;                            // +0x15
        }
    }
}