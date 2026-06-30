// FUNC_NAME: Heap::TrimFreeBlocks
int Heap::TrimFreeBlocks(int minBlockSize) {
    CriticalSection* cs = *(CriticalSection**)(this + 0x4E8);
    if (cs != nullptr) {
        EnterCriticalSection(cs);
        // Increment a debug counter? (unusual operation)
        cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo->Type + 1);
    }

    ListNode* currentNode = *(ListNode**)(this + 0x460);
    int totalFreed = 0;
    int freedThisIteration = 0;

    // Iterate over the free list (singly linked via +0x18, sentinel at this+0x448)
    while (currentNode != (ListNode*)(this + 0x448)) {
        // Check if block is free (flag at +0xD) and if it's a normal block (flag at +0xF?)
        if (*(char*)(currentNode + 0xD) != '\0') {
            // Compute block header pointer (relative offset from node location)
            int* headerPtr = (int*)(*(int*)(currentNode + 4) - 0x10 + (int)currentNode);
            // Check low bit of a flag at header-relative offset (probably "in use" flag)
            if ((*(byte*)(*(int*)(currentNode + 4) - 0xC + (int)currentNode) & 1) == 0) {
                // Another flag check (maybe "coalesce" or "decommit allowed")
                if (*(char*)(currentNode + 0xF) != '\0') {
                    // Compute real block base (subtracting previous block's size?)
                    HeapBlockHeader* block = (HeapBlockHeader*)((int)headerPtr - *headerPtr);
                    uint32_t blockSize = *(uint32_t*)(block + 4) & 0x7FFFFFF8;

                    // Only consider blocks larger than (minBlockSize + 0x40)
                    if (minBlockSize + 0x40 < blockSize) {
                        uint32_t excess = blockSize - (minBlockSize + 0x40);
                        uint32_t pageSize = (*(uint32_t*)(this + 0x4E0) >> 1) + 0xFFFF & 0xFFFF0000;
                        uint32_t decommitSize = pageSize;

                        // Find largest multiple of pageSize <= excess
                        if (pageSize * 2 < excess) {
                            uint32_t iterSize = pageSize * 2;
                            do {
                                iterSize += pageSize;
                                decommitSize += pageSize;
                            } while (iterSize < excess);
                        }

                        // Attempt to decommit memory using VirtualFree
                        if (decommitSize < excess) {
                            void* addr = (void*)((*(int*)(currentNode + 4) - decommitSize) + (int)currentNode);
                            BOOL result = VirtualFree(addr, decommitSize, MEM_DECOMMIT);
                            if (result) {
                                totalFreed += decommitSize;
                                freedThisIteration = totalFreed;
                                // Update block header size (subtract decommitted portion)
                                *(int*)(currentNode + 4) -= decommitSize;
                                if (block != *(HeapBlockHeader**)(this + 0x440)) {
                                    // Remove block from current free list
                                    *(undefined4*)(*(int*)(block + 8) + 0xC) = *(undefined4*)(block + 0xC);
                                    *(undefined4*)(*(int*)(block + 0xC) + 8) = *(undefined4*)(block + 8);
                                }
                                // Update block size with new flags
                                uint32_t newSize = (blockSize - decommitSize) + 0x10;
                                newSize = (newSize & 0x7FFFFFF8) | (*(uint32_t*)(block + 4) & 0x80000007);
                                *(uint32_t*)(block + 4) = newSize;

                                // Call helper to fix free list (merge adjacent free blocks)
                                MergeAdjacentBlocks();

                                // Reinsert block into a different free list (small blocks list?)
                                if (block != *(HeapBlockHeader**)(this + 0x440)) {
                                    int tail = *(int*)(this + 0x3C);
                                    block[2] = (int)(this + 0x30);  // +8 -> next
                                    block[3] = tail;               // +C -> prev
                                    *(int*)(this + 0x3C) = (int)block;
                                    *(int*)(tail + 8) = (int)block;
                                }
                            }
                        }
                    }
                }
            }
        }
        currentNode = *(ListNode**)(currentNode + 0x18);
    }

    if (cs != nullptr) {
        // Decrement debug counter? (mirror of increment)
        cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(cs);
    }
    return totalFreed;
}