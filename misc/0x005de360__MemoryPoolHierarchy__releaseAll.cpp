// FUNC_NAME: MemoryPoolHierarchy::releaseAll
void __thiscall MemoryPoolHierarchy::releaseAll(void) {
    uint numPages;
    int *pageArray;
    int *pageList;
    int *currentPage;
    int *pageFreeList;
    int pageCount;
    int *blockList;
    int *currentBlock;
    int *blockFreeList;
    int blockCount;
    int *elementList;
    int *currentElement;
    int *elementFreeList;
    int elementCount;
    uint pageIndex;

    // +0x2B: number of pages in the active array
    numPages = this->pageCount; // offset 0x2B (43)
    pageIndex = 0;
    if (numPages != 0) {
        do {
            // +0x2A: pointer to array of page pointers
            currentPage = *(int **)(this->pageArray + pageIndex * 4); // offset 0x2A (42)
            if (currentPage != (int *)0x0) {
                // Page structure: 
                // +0x00: block list head (linked list of blocks)
                blockList = (int *)*currentPage;
                // +0x10 (10): number of blocks in this page
                pageCount = currentPage[10];
                for (int i = 0; i < pageCount; i++) {
                    currentBlock = blockList;
                    if (blockList != (int *)0x0) {
                        // Block structure:
                        // +0x00: element list head (linked list of elements)
                        elementList = (int *)*blockList;
                        // +0x12 (18): number of elements in this block
                        blockCount = blockList[0x12];
                        for (int j = 0; j < blockCount; j++) {
                            currentElement = elementList;
                            if (elementList != (int *)0x0) {
                                // Element structure:
                                // +0x0B (11): next element pointer (for relinking)
                                elementFreeList = (int *)elementList[0xb];
                                // Move element to manager's small-object free list
                                // +0x29: small object free list head
                                *elementList = (int)this->smallObjectFreeList; // offset 0x29
                                // +0x20: used small object count
                                this->usedSmallCount -= 1; // offset 0x20
                                // +0x1F: free small object count
                                this->freeSmallCount += 1; // offset 0x1F
                                // Update head
                                this->smallObjectFreeList = elementList;
                            }
                            elementList = elementFreeList;
                        }
                        // After processing all elements, move block to block free list
                        blockFreeList = (int *)blockList[0x13];
                        // +0x1B: block free list head
                        *blockList = (int)this->blockFreeList; // offset 0x1B
                        // +0x12: used block count
                        this->usedBlockCount -= 1; // offset 0x12
                        // +0x11: free block count
                        this->freeBlockCount += 1; // offset 0x11
                        this->blockFreeList = blockList;
                    }
                    blockList = blockFreeList;
                }
                // Move page to page free list
                // +0x0D: page free list head
                *currentPage = (int)this->pageFreeList; // offset 0x0D
                // +0x04: used page count
                this->usedPageCount -= 1; // offset 0x04
                // +0x03: free page count
                this->freePageCount += 1; // offset 0x03
                this->pageFreeList = currentPage;
            }
            pageIndex++;
        } while (pageIndex < numPages);
    }
    this->pageCount = 0; // +0x2B
    // Free the page array itself (FUN_009c8f10 likely a deallocation function)
    FUN_009c8f10(this->pageArray); // +0x2A
    this->pageArray = 0;
    this->someOtherCount = 0; // +0x2C
    // Call virtual methods on sub-managers? (through vtable at +0x0, +0x0E, +0x1C)
    (*(this->vtable + 4))(); // offset 0x0, second vtable entry
    (*(int (**)(void))(this->subManager1Vtable + 4))(); // offset 0x0E
    (*(int (**)(void))(this->subManager2Vtable + 4))(); // offset 0x1C
    return;
}