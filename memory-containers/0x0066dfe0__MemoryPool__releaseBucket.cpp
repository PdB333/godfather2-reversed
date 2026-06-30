// FUNC_NAME: MemoryPool::releaseBucket
void __fastcall MemoryPool::releaseBucket(MemoryPool* thisPtr, Bucket* bucket)
{
    // Iterate through the pool's bucket array to locate the given bucket
    Bucket* iterBucket = &thisPtr->buckets[0]; // base of bucket array at offset 0x122A8
    uint bucketIndex = 0;

    do {
        if (bucket == iterBucket) {
            // Found the bucket: release all allocations in its allocation list
            AllocNode* currentNode = bucket->allocList; // bucket + 0x14
            while (currentNode != nullptr) {
                AllocNode* nextNode = currentNode->next; // node + 0x00

                // Update global counters
                thisPtr->totalAllocatedSize -= currentNode->size; // this + 0x04
                bucket->totalSize -= currentNode->size; // bucket + 0x0C
                bucket->numAllocs--; // bucket + 0x10

                // Return node to global free list
                currentNode->next = thisPtr->freeListHead; // this + 0x14
                currentNode->unknown1 = 0; // node + 0x04
                currentNode->size = 0; // node + 0x0C

                // Decrement global small counter (16-bit)
                *(short*)(&thisPtr->bucketCount) = (short)thisPtr->bucketCount - 1; // this + 0x08

                thisPtr->freeListHead = (int)currentNode; // update free list head

                currentNode = nextNode;
            }

            // Clear the bucket fields
            bucket->head = nullptr; // +0x00
            bucket->someCount = 0; // +0x04
            bucket->totalSize = 0; // +0x0C
            bucket->numAllocs = 0; // +0x10
            bucket->allocList = nullptr; // +0x14
            bucket->unknown1 = 0; // +0x18
            bucket->unknown2 = 0; // +0x1C? Actually bucket[1] set to 0

            // Decrement global bucket count
            thisPtr->totalBuckets--; // +0x00

            return;
        }
        bucketIndex++;
        iterBucket++;
    } while (bucketIndex < 144); // 0x90 = 144 buckets
}