// FUNC_NAME: HashTable::rehash
void HashTable::rehash(int newBucketCount) {
    void* newBuckets = nullptr;
    int allocSize = newBucketCount * 4;

    // Allocate new bucket array
    if (allocSize == 0) {
        newBuckets = nullptr;
    } else {
        if (allocSize < (int)0xfffffffd) {
            newBuckets = (void*)(*g_allocFunc)(0, allocSize);
            if (newBuckets == nullptr) {
                if (this != nullptr) {
                    handleAllocError(); // FUN_00635a80
                    return;
                }
                newBuckets = nullptr;
            }
        } else {
            reportAllocError(this, "memory allocation error: block too big"); // FUN_00633920
        }
        if (this != nullptr) {
            BucketManager* mgr = *(BucketManager**)((int)this + 0x10);
            mgr->totalAllocated += allocSize; // +0x24
        }
    }

    BucketManager* mgr = *(BucketManager**)((int)this + 0x10);
    int oldBucketCount = mgr->bucketCount; // +0x08 (third field)

    // Zero out new buckets
    int count = newBucketCount;
    void** writePtr = (void**)newBuckets;
    while (count > 0) {
        *writePtr = nullptr;
        writePtr++;
        count--;
    }

    int bucketIndex = 0;
    if (oldBucketCount > 0) {
        do {
            // Get head of old bucket chain
            void* entry = *((void**)mgr->buckets + bucketIndex);
            if (entry != nullptr) {
                do {
                    void* nextEntry = *(void**)entry; // linked list next pointer
                    int hash = *(int*)((int)entry + 8); // +0x08: hash value
                    uint newIndex = hash & (newBucketCount - 1);
                    // Insert at head of new bucket
                    *(void**)entry = ((void**)newBuckets)[newIndex];
                    ((void**)newBuckets)[newIndex] = entry;
                    entry = nextEntry;
                } while (entry != nullptr);
            }
            bucketIndex++;
        } while (bucketIndex < oldBucketCount);
    }

    // Free old bucket array and update manager
    int oldSize = mgr->bucketCount;
    void* oldBuckets = mgr->buckets;
    if (oldBuckets != nullptr) {
        (*g_freeFunc)(oldBuckets);
        BucketManager* mgr = *(BucketManager**)((int)this + 0x10);
        mgr->totalAllocated -= oldSize * 4;
    }
    mgr->buckets = (void**)newBuckets;
    mgr->bucketCount = newBucketCount;

    return;
}