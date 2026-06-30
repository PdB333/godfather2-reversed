// FUNC_NAME: HeapManager::splitBlock
// This function splits a free memory block into an allocated block (at the free block's address) and a remainder free block.
// The remainder is inserted into the heap's free list.
// Parameters:
//   this (ECX) - pointer to heap manager (param_2 in decompiled)
//   freeBlock (EAX) - pointer to the free block header being split
//   remainderBlock (stack param1) - pointer to the new remainder free block header (lower address)
//   allocationSize (stack param3) - total size of the allocation (including header)
void __thiscall HeapManager::splitBlock(HeapManager* thisHeap, FreeBlockHeader* freeBlock,
                                        FreeBlockHeader* remainderBlock, uint32_t allocationSize)
{
    // Compute the total bytes taken from the original free block:
    // offset from freeBlock to remainderBlock (since remainder is lower) + allocationSize
    uint32_t takenBytes = (uint32_t(remainderBlock) - uint32_t(freeBlock)) + allocationSize;

    // Compute the size of the remainder block (should be freeBlock - remainderBlock, positive)
    uint32_t remainderSize = allocationSize - takenBytes; // actually = freeBlock - remainderBlock

    // If the remainder is too small (less than minimum block size), do not split;
    // instead mark the allocation flag at the end of the allocated region.
    if (remainderSize < 0x10) {
        uint32_t* flagPtr = (uint32_t*)(uint32_t(remainderBlock) + 4 + allocationSize);
        *flagPtr |= 1; // Set the "in use" flag
        return;
    }

    // Unlink the old free block from its list? Actually we are inserting the new remainder block.
    // Get the current head of the free list (at offset 0x3C in the heap)
    FreeBlockHeader* oldHead = *(FreeBlockHeader**)((uint8_t*)thisHeap + 0x3C);

    // Set up the new remainder block's linked list pointers
    remainderBlock->next = oldHead;                     // +0x0C
    FreeBlockHeader** listHead = (FreeBlockHeader**)((uint8_t*)thisHeap + 0x30);
    remainderBlock->prev = *listHead;                   // +0x08

    // Insert the remainder block at the head of the free list
    *listHead = remainderBlock;                         // +0x30 of heap? Actually the head pointer is at heap+0x30
    oldHead->prev = remainderBlock;                     // +0x08 of old head

    // If the remainder block is smaller than a threshold (0x200), also update a special pointer at heap+0x444
    if (remainderSize < 0x200) {
        *(FreeBlockHeader**)((uint8_t*)thisHeap + 0x444) = remainderBlock;
    }

    // Set the size/flags of the allocated block (original free block's header)
    freeBlock->sizeAndFlags = takenBytes;               // +0x04

    // Set the allocation flag at the end of the allocated block
    uint32_t* endFlagPtr = (uint32_t*)(takenBytes + 4 + uint32_t(freeBlock));
    *endFlagPtr |= 1;

    // Set the header of the new remainder block
    remainderBlock->sizeAndFlags = remainderSize | 1;   // +0x04
    // Set the footer of the new remainder block (for coalescing)
    *(uint32_t*)(uint32_t(remainderBlock) + remainderSize) = remainderSize; // footer at offset size
}