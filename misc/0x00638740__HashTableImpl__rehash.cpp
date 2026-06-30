// FUNC_NAME: HashTableImpl::rehash

void __thiscall HashTableImpl::rehash(int thisObject, int newBucketCount) {
    int *bucketArrayPtr;
    int *allocHeader;
    int *entryPtr;
    int *nextEntry;
    uint hashIndex;
    undefined4 *newBucketArray;
    undefined4 *currentBucket;
    int i;

    // Calculate size of new bucket array (each entry is a pointer)
    uint allocSize = newBucketCount * 4;

    // Attempt to allocate new bucket array
    newBucketArray = (undefined4 *)0x0;
    if (allocSize == 0) {
        goto skip_alloc;
    }

    if (allocSize < 0xfffffffd) {
        newBucketArray = (undefined4 *)(*DAT_012059dc)(0, allocSize); // operator new
        if (newBucketArray == (undefined4 *)0x0) {
            if (thisObject != 0) {
                // Allocation failure – likely error callback
                FUN_00635a80();
                return;
            }
            goto skip_alloc;
        }
    } else {
        // Block too big
        FUN_00633920(thisObject, "memory allocation error: block too big");
        return;
    }

    // Update memory tracking counter at offset +0x24 in the allocator header
    if (thisObject != 0) {
        allocHeader = (int *)(*(int *)(thisObject + 0x10) + 0x24);
        *allocHeader = *allocHeader + allocSize;
    }

skip_alloc:
    // Get pointer to the hash table metadata structure
    bucketArrayPtr = *(int **)(thisObject + 0x10);
    int remaining = newBucketCount;
    currentBucket = newBucketArray;

    // Zero-initialize the new bucket array
    if (0 < newBucketCount) {
        for (; remaining != 0; remaining--) {
            *currentBucket = 0;
            currentBucket++;
        }
    }

    // Rehash all existing entries
    int oldBucketCount = bucketArrayPtr[2]; // Number of old buckets
    for (i = 0; i < oldBucketCount; i++) {
        entryPtr = *(int **)(*bucketArrayPtr + i * 4); // Entry in current bucket
        if (entryPtr != (int *)0x0) {
            do {
                nextEntry = (int *)*entryPtr; // Save next pointer before overwriting
                // Compute new bucket index using mask (bucket count must be power of two)
                hashIndex = entryPtr[2] & (newBucketCount - 1U);
                *entryPtr = newBucketArray[hashIndex]; // Insert at head
                newBucketArray[hashIndex] = (undefined4)entryPtr;
                entryPtr = nextEntry;
            } while (nextEntry != (int *)0x0);
        }
    }

    // Free the old bucket array
    int oldCount = bucketArrayPtr[2];
    if (*bucketArrayPtr != 0) {
        (*DAT_012059e0)(*bucketArrayPtr); // operator delete
        // Decrement memory tracking counter
        int *counterPtr = (int *)(*(int *)(thisObject + 0x10) + 0x24);
        *counterPtr = *counterPtr + oldCount * -4;
    }

    // Update metadata
    *bucketArrayPtr = (int)newBucketArray;
    bucketArrayPtr[2] = newBucketCount;
    return;
}