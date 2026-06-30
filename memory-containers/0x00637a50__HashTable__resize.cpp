// FUNC_NAME: HashTable::resize
// Address: 0x00637a50
// Purpose: Resizes the hash table to a new capacity (param_2). Handles both growth and shrinkage.
// The table uses separate chaining with bucket nodes of 20 bytes each.
// In this engine, the bucket array is pre-allocated based on capacity (power of two).
void __thiscall HashTable::resize(int newSize, int aFlag) {
    byte capacityShift = *(byte *)(this + 0x7); // m_capacityShift: exponent for bucket count
    int currentCount = *(int *)(this + 0x1c);   // m_elementCount: number of stored elements
    BucketNode** oldBuckets = *(BucketNode***)(this + 0x10); // m_buckets array

    // If the table is empty (capacityShift == 0), capture the first bucket's data and clear it.
    if (capacityShift == 0) {
        // Save first bucket's key-value pair onto stack (temporary)
        local_1c = oldBuckets[0]->key;
        local_14 = oldBuckets[0]->value;
        uStack_10 = *(undefined4 *)((int)oldBuckets[0] + 0xc); // possibly the next pointer?
        local_c = oldBuckets[0]->extra;
        oldBuckets = (BucketNode**)&local_1c; // Redirect to stack copy? This seems like a bug or unusual pattern.
        // Clear some fields in the table header (likely stats or free list)
        *(int *)(this + 0x10 + 0x40) = 0; // m_freeListHead? 
        *(int *)(this + 0x10 + 0x48) = 0; // m_freeListTail?
    }

    // If new size is larger, allocate more memory for the raw data array (8-byte entries)
    if (currentCount < newSize) {
        FUN_00637910(newSize); // Possibly m_data reallocation
    }

    // Rehash all elements (likely move them to correct buckets)
    FUN_00637960(this, aFlag);

    // If new size is smaller, we need to shrink the data array and update bucket links.
    if (newSize < currentCount) {
        int shrinkCount = currentCount - newSize;
        *(int *)(this + 0x1c) = newSize;
        int srcOffset = newSize * 8;
        // Iterate over elements that are being removed (from newSize to oldCount)
        do {
            int* srcElem = (int*)(*(int*)(this + 0xc) + srcOffset); // m_data[newSize + i]
            if (*srcElem != 0) {
                int* newElem;
                // Attempt to allocate a new node from a pool? Possibly get a free bucket node.
                newElem = (int*)FUN_00637f10();
                if (newElem == &DAT_00e2a93c) { // Sentinel value indicating no free nodes
                    newElem = (int*)FUN_00637d60(this); // Allocate a new node
                }
                // Copy key and value (8 bytes) to the new node
                newElem[0] = srcElem[0];
                newElem[1] = srcElem[1];
            }
            srcOffset += 8;
            shrinkCount--;
        } while (shrinkCount != 0);
        // Reallocate the data array to the new size
        int newData = FUN_006279a0(currentCount * 8, newSize * 8); // resizing memory block
        *(int*)(this + 0xc) = newData;
    }

    // Now rehash the bucket chains (the old buckets still have pointers to data)
    int bucketCount = 1 << (capacityShift & 0x1f);
    int i = bucketCount - 1;
    // Iterate over all buckets, moving any remaining non-null entries to the new table
    // Each bucket entry is 20 bytes, and we access the key-value part at offset +8.
    if (i >= 0) {
        int* bucketEntry = (int*)((int)oldBuckets + i * 0x14 + 8); // start at last bucket's key-value
        do {
            if (*bucketEntry != 0) {
                int* newBucketEntry = (int*)FUN_00638020(this); // Get a new bucket node from free list or allocator
                newBucketEntry[0] = bucketEntry[0];
                newBucketEntry[1] = bucketEntry[1];
            }
            i--;
            bucketEntry -= 5; // move to previous bucket entry (5 ints = 20 bytes)
        } while (i >= 0);
    }

    // If the table was non-empty and we have bucket nodes to free, update the free list.
    // Also may need to release the old bucket array memory (not shown here).
    if ((capacityShift != 0) && (oldBuckets != nullptr)) {
        // Free the old bucket array? The call to (*DAT_012059e0)(oldBuckets) is likely a deallocation function.
        (*DAT_012059e0)(oldBuckets);
        if (this != 0) {
            // Update the bucket array pointer? It's subtracting total bytes of the old bucket array from something.
            int* bucketSizeCounter = (int*)(*(int*)(this + 0x10) + 0x24);
            *bucketSizeCounter = *bucketSizeCounter + bucketCount * -0x14; // Subtract the old bucket array size
        }
    }
    return;
}