// FUNC_NAME: MemoryPool::freeBlock
void MemoryPool::freeBlock() {
    // This function frees a block identified by the index in EDI (unaff_EDI).
    // It decrements the reference count at offset 0x0E.
    // If the count reaches zero, the block is unlinked from the hash table
    // and returned to the free list. Total allocated size is updated,
    // and if it exceeds a threshold, compaction is triggered.
    // When all blocks are freed, the pool is destroyed.

    int blockIndex = unaff_EDI; // index passed via register
    int iVar2 = *(int *)(g_poolBlocksPtr + blockIndex * 4);
    short* refCountPtr = (short*)(iVar2 + 0x0E);
    *refCountPtr = *refCountPtr - 1;

    if (*refCountPtr == 0) {
        // Block is no longer referenced; remove from hash table
        uint hashValue = *(uint*)(iVar2 + 8) % g_hashTableSize;
        int* bucketHeadPtr = &g_hashTable[hashValue];
        int currentBlock = *bucketHeadPtr;

        while (currentBlock != 0) {
            // iVar4 = g_poolBlocksPtr (already loaded)
            int actualBlock = *(int*)(g_poolBlocksPtr + currentBlock * 4);
            if (actualBlock == iVar2) {
                *bucketHeadPtr = *(int*)(iVar2 + 4); // remove from hash bucket
                break;
            }
            bucketHeadPtr = (int*)(currentBlock + 4);
            currentBlock = *bucketHeadPtr;
        }

        // Update total allocated size and free list
        uint blockSize = (uint)*(ushort*)(*(int*)(g_poolBlocksPtr + blockIndex * 4) + 0x0C);
        g_totalAllocSize += 0x14 + blockSize; // header size (20) + block size

        uint freeListEntry = (blockIndex * 2) | 1; // encode index into free list value
        *(int*)(g_poolBlocksPtr + blockIndex * 4) = g_freeListHead;
        g_freeListHead = freeListEntry;

        if (g_totalAllocSize > 0x8000) {
            MemoryPool::compactMemory(); // FUN_0065a310
        }

        g_activeAllocCount -= 1;
        if (g_activeAllocCount == 0) {
            // All blocks freed; destroy pool
            free(g_hashTable);
            g_hashTable = 0;
            free(g_poolBlocksPtr);
            g_poolBlocksPtr = 0;

            if (g_otherPoolPtr != 0) {
                MemoryPool::reclaimOtherPool(); // FUN_0065bdf0
                someDeleteFunction(g_otherPoolPtr); // FUN_009c8eb0
            }
        }
    }
}