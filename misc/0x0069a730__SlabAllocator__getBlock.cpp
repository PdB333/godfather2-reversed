// FUNC_NAME: SlabAllocator::getBlock
// Address: 0x0069a730
// Role: Resolves a block pointer from the slab allocator. Handles direct blocks and blocks in a linked list.
// Offsets: this+0x04 = m_pCurrentBlock (pointer to current working block)
//          this+0x14 = m_bUseList (flag: if non-zero, use linked list for block retrieval)
//          param_3 = base pointer of a block to resolve (may be currentBlock or a node in a list)
//          param_4 = original size/key (upper 8 bits used for alignment to 0x100 boundary)
//          FUN_004d4b20 likely checks if a block is free/valid (returns <0 if valid/allocated)
//          FUN_00699df0 copies block data from source to output
//          FUN_0069a2a0 aligns size to 256-byte boundary and returns a pointer to the aligned block
//          FUN_00ab3c50 possibly gets the next pointer from a block header (e.g., +0 offset)

__thiscall uint* SlabAllocator::getBlock(void* this, uint* output, int* blockPtr, uint originalSize) {
    uint originalSizeCopy;
    int* nextBlock;
    int test1;
    uint* alignedResult;
    uint8 tempBuf[8];

    originalSizeCopy = originalSize;
    // Check if blockPtr is the start of the current block or points to the current block pointer itself
    if ((blockPtr == *(int**)((int)this + 4)) || (blockPtr == (int*)((int)this + 4))) {
        // If the list flag is set and the block is considered valid/allocated
        if ((*(int*)((int)this + 0x14) != 0) && (test1 = FUN_004d4b20(originalSize), test1 < 0)) {
            // Copy from the current block directly
            FUN_00699df0(output, *(int*)((int)this + 4), originalSize, 0);
            return output;
        }
        // Otherwise align size to 256 bytes and get the block from the aligned pool
        originalSize = originalSize & 0xffffff00;
        alignedResult = (uint*)FUN_0069a2a0((uint8*)tempBuf, originalSizeCopy, originalSize);
        *output = *alignedResult;
        return output;
    }

    // Not the current block: follow linked list chain (likely a node header)
    nextBlock = (int*)FUN_00ab3c50(blockPtr);
    test1 = FUN_004d4b20(originalSize);
    if ((test1 < 0) && (test1 = FUN_004d4b20(nextBlock + 4), test1 < 0)) {
        // If the block or its neighbor is still valid, handle with list traversal
        test1 = *blockPtr;  // original block's first word (maybe next pointer or tag)
        if (test1 != 0) {
            blockPtr = nextBlock; // use the linked list node
        }
        FUN_00699df0(output, blockPtr, originalSize, test1 != 0); // flag indicates whether list was used
        return output;
    }

    // Fallback: align and get from pool
    originalSize = originalSize & 0xffffff00;
    alignedResult = (uint*)FUN_0069a2a0((uint8*)tempBuf, originalSizeCopy, originalSize);
    *output = *alignedResult;
    return output;
}