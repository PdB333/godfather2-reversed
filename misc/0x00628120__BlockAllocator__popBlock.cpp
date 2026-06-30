// FUNC_NAME: BlockAllocator::popBlock
// Address: 0x00628120
// Role: Pops a block from the allocator's head position. Reuses memory from one of three allocation sources
//       based on the block's type field. Returns 1 if successful, 0 if the block's predecessor is a free sentinel.

int __thiscall BlockAllocator::popBlock(BlockAllocator* this)
{
    int blockType;
    int blockSize;          // stored at pHead[-1] (offset -0x4)
    int* pNewBlock;
    int* pHead;             // stored at this+0x8
    int* pCursor;

    BaseAllocator::initialize(this);                    // 0x00625ca0

    pHead = *(int**)(this + 0x8);                       // +0x8: head pointer

    blockType = *(int*)(pHead - 2);                     // -0x8: block type/size ID
    blockSize = *(int*)(pHead - 1);                     // -0x4: block size or flags

    if (blockType == 3) {
        // Check if the integer representation of the float is identical (special marker)
        if ((float)(int)*(float*)(pHead - 1) == *(float*)(pHead - 1)) {
            pNewBlock = (int*)allocateFromType3Pool();  // 0x00637f10
            goto copyBlock;
        }
    } else if (blockType == 4) {
        pNewBlock = (int*)allocateFromType4Pool();      // 0x00637f90
        goto copyBlock;
    }

    pNewBlock = (int*)allocateFromDefaultPool();        // 0x00637ea0

copyBlock:
    // Overwrite the current block with the newly allocated pair
    *(int*)(pHead - 2) = *pNewBlock;
    *(int*)(pHead - 1) = pNewBlock[1];

    // Reload head pointer (may have been modified by allocation)
    pHead = *(int**)(this + 0x8);

    // If there is a free sentinel two blocks before head (type==0), move head back by two blocks
    if ((pHead - 2 != NULL) && (*(int*)(pHead - 2) == 0)) {
        *(int**)(this + 0x8) = pHead - 4;               // move head back 16 bytes (2 blocks)
        return 0;
    }

    // Compact the list: shift elements from head-2 down by one block
    for (pCursor = pHead - 2; pCursor < pHead; pCursor += 2) {
        *(int*)(pCursor - 2) = *pCursor;
        *(int*)(pCursor - 1) = *(pCursor + 1);
    }

    // Move head back by one block (8 bytes)
    *(int**)(this + 0x8) = pHead - 2;
    return 1;
}