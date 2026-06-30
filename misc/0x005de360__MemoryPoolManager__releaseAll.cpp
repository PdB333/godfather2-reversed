// FUNC_NAME: MemoryPoolManager::releaseAll
void MemoryPoolManager::releaseAll()
{
    uint numPools = this->numPools;                      // +0x2b
    uint localCounter = 0;

    if (numPools != 0) {
        do {
            Pool* pool = this->pools[localCounter];      // +0x2a: array of Pool*
            if (pool != nullptr) {
                LargeBlock* largeBlock = pool->firstLargeBlock; // *pool (offset 0)
                int largeBlockCount = pool->largeBlockCount;     // +0x28 (pool[10])

                for (; largeBlockCount != 0; largeBlockCount--) {
                    MediumBlock* mediumBlock = largeBlock->firstMediumBlock; // *largeBlock (offset 0)
                    if (mediumBlock != nullptr) {
                        int mediumBlockCount = largeBlock->mediumBlockCount; // +0x48 (largeBlock[0x12])

                        for (; mediumBlockCount != 0; mediumBlockCount--) {
                            SmallBlock* smallBlock = mediumBlock->firstSmallBlock; // *mediumBlock (offset 0)
                            if (smallBlock != nullptr) {
                                SmallBlock* nextSmall = (SmallBlock*)smallBlock->next; // +0x2c (smallBlock[0xb])
                                // Move small block to free list
                                smallBlock->next = (SmallBlock*)this->freeListSmall; // +0x29
                                this->allocatedSmallCount--;      // +0x20
                                this->freedSmallCount++;          // +0x1f
                                this->freeListSmall = smallBlock; // +0x29
                            }
                            mediumBlock = nextSmall;
                        }
                        // Move medium block to free list
                        MediumBlock* nextMedium = (MediumBlock*)largeBlock->nextMedium; // +0x4c (largeBlock[0x13])
                        mediumBlock->next = (MediumBlock*)this->freeListMedium; // +0x1b
                        this->allocatedMediumCount--;      // +0x12
                        this->freedMediumCount++;          // +0x11
                        this->freeListMedium = mediumBlock; // +0x1b
                    }
                    largeBlock = nextMedium;
                }
                // Move large block to free list
                largeBlock->next = (LargeBlock*)this->freeListLarge; // +0xd
                this->allocatedLargeCount--;      // +0x4
                this->freedLargeCount++;          // +0x3
                this->freeListLarge = largeBlock; // +0xd
            }
            localCounter++;
        } while (localCounter < numPools);
    }

    this->numPools = 0;
    FUN_009c8f10(this->pools); // free the pool array itself
    this->pools = 0;
    this->someFlag = 0; // +0x2c

    // Call virtual destructors or cleanup on this and two sub-objects
    (this->vtable->cleanup)();  // vtable+4
    (this->subPoolA->vtable->cleanup)(); // +0xe
    (this->subPoolB->vtable->cleanup)(); // +0x1c
}