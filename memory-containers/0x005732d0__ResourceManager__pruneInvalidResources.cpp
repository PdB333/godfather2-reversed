// FUNC_NAME: ResourceManager::pruneInvalidResources
void ResourceManager::pruneInvalidResources(ResourceManager *this, ResourceEntry **entries, uint count) {
    uint i;
    ResourceEntry *entry;
    char *stringPtr;
    char *sentinelStr1;
    char *sentinelStr2;
    int flags;
    int refCount;
    MemoryPoolHeader *pool;

    // Process each entry looking for invalid resources (sentinel patterns)
    for (i = 0; i < count; i++) {
        entry = entries[i];
        flags = entry->flags;          // +0x2C
        refCount = entry->refCount;    // +0x00
        // Determine which string slot to check (based on bit 5 of flags and refCount < 2)
        if ((flags & 0x20) == 0 || refCount < 2) {
            stringPtr = entry->stringSlotA;   // +0x10
        } else {
            stringPtr = entry->stringSlotB;   // +0x18
        }
        if (stringPtr != nullptr) {
            // Check for magic resource identifier: bytes 0x04, 0x02 at start
            if (stringPtr[0] == '\x04' && stringPtr[1] == '\x02') {
                // At offset 8 there is a pair of pointers to sentinel strings
                ResourceSentinel *sentinelList = *(ResourceSentinel **)(stringPtr + 8);
                sentinelStr1 = sentinelList->str1;         // first pointer
                sentinelStr2 = sentinelList->str2;         // second pointer
                // Sentinel patterns: str1 = "\n\0\0" (newline, two nulls); str2 = "\v\0\0\0\0" (vertical tab, float zero)
                if (*sentinelStr1 == '\n' && *(short *)(sentinelStr1 + 2) == 0 &&
                    *sentinelStr2 == '\v' && *(float *)(sentinelStr2 + 4) == 0.0f) {
                    // This entry is invalid – clear its string slot
                    if ((flags & 0x20) == 0 || refCount < 2) {
                        entry->stringSlotA = nullptr;
                    } else {
                        entry->stringSlotB = nullptr;
                    }
                    continue; // skip setting dirty flag
                }
            }
            // Resource not invalid, mark pool as dirty
            this->dirtyFlag = 1; // +0x3C
        }
    }

    // Allocate a new memory block in the pool if there were any entries to process
    if (count != 0) {
        pool = this->pool; // +0x2C
        // Use the pool's allocator (vtable function at first pointer)
        MemoryPoolBlock *newBlock = pool->allocator->allocate(0x10, (int *)&someOutput); // size 16, extra arg
        newBlock->returnAddr = savedRetAddr; // likely a debugging/tracking value
        newBlock->count = count;
        newBlock->byteField = 0; // set to 0 at offset 8
        newBlock->next = pool->lastBlock; // link to previous last
        pool->totalEntries += count;
        pool->lastBlock = newBlock;
        pool->someFlag = 1; // mark that new block was added
    }
}