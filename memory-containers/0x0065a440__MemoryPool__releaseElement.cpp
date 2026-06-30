// FUNC_NAME: MemoryPool::releaseElement
// Address: 0x0065a440
// Role: Decrements reference count on a pooled element and frees it when count reaches zero.
//        Removes element from hash table and returns it to the free list.
//        If all elements are freed, deallocates the pool.

void MemoryPool::releaseElement(int index) {
    int* bucketHeadPtr;
    int current;
    int next;
    int hashIndex;
    int freeListHead;
    int totalAllocatedSize;
    int elementPtr;

    // index is passed in EDI (unaff_EDI)
    int* poolArray = g_poolArray; // DAT_01205a34 - array of element pointers/free IDs
    elementPtr = *(int*)(poolArray + index * 4); // element address

    // Decrement reference count at offset 0x0E
    *(short*)(elementPtr + 0x0E) = *(short*)(elementPtr + 0x0E) - 1;

    if (*(short*)(elementPtr + 0x0E) == 0) {
        // Compute hash bucket index from element's hash key (offset 0x08)
        hashIndex = *(uint*)(elementPtr + 0x08) % g_hashTableSize; // DAT_01205a3c

        // Find and remove the element from the hash chain (single linked list)
        bucketHeadPtr = (int*)(g_hashTable + hashIndex * 4); // DAT_01205a38 + hashIndex*4
        current = *(int*)(g_hashTable + hashIndex * 4);
        while (current != 0) {
            current = *(int*)(poolArray + *bucketHeadPtr * 4);
            if (current == elementPtr) {
                // Unlink: set bucket head to the next element in chain
                *bucketHeadPtr = *(int*)(elementPtr + 0x04);
                break;
            }
            bucketHeadPtr = (int*)(current + 0x04);
        }

        // Update total allocated size: add header (0x14) plus user size at offset 0x0C
        totalAllocatedSize = g_totalAllocatedSize; // DAT_01205a50
        g_totalAllocatedSize = totalAllocatedSize + 0x14 + (uint)*(ushort*)(*(int*)(poolArray + index * 4) + 0x0C);

        // Return element to free list
        freeListHead = g_freeListHead; // DAT_01205a44
        *(int*)(poolArray + index * 4) = freeListHead; // Store old free head in slot (marks as free)
        g_freeListHead = index * 2 | 1; // New free head ID (odd index*2|1)

        // If total allocated size exceeds threshold (0x8000), trigger cleanup
        if (0x8000 < g_totalAllocatedSize) {
            FUN_0065a310(); // likely "growRegion" or "compactPool"
        }

        g_activeCount = g_activeCount - 1; // DAT_01205a48
        if (g_activeCount == 0) {
            // All elements freed: destroy the pool
            free(g_hashTable); // DAT_01205a38
            g_hashTable = 0;
            free(g_poolArray); // DAT_01205a34
            // g_poolArray set after free? Actually code: (*(code *)PTR__free_00f0cd8c)(DAT_01205a34);
            // Then sets DAT_01205a34 = 0;
            g_poolArray = 0;

            if (g_poolMemoryBase != 0) { // DAT_01205a4c
                FUN_0065bdf0(); // Possibly "poolCleanup"
                FUN_009c8eb0(g_poolMemoryBase); // free the memory base
            }
        }
    }
}