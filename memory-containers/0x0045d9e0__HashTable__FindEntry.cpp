// FUNC_NAME: HashTable::FindEntry
int* HashTable::FindEntry(unsigned int hashKey) {
    bool bVar1;
    char isCollision;
    int collisionCount1;
    int collisionCount2;
    int bucketArray[18]; // stack buffer for collision chain iteration
    int* currentBucket;

    // Compute hash and acquire lock (or maybe initialize iteration)
    this->hashFunction(hashKey, 0xae986323); // Constant might be a salt or seed
    this->lockAcquire(4); // Possibly a spinlock or semaphore

    if (isCollision == '\0') {
        bVar1 = *currentBucket == 0; // No collision: check if bucket is empty
    } else {
        bVar1 = collisionCount1 == collisionCount2; // Collision chain: compare counters
    }
    if (bVar1) {
        return (int*)0x0; // Not found
    }

    if (isCollision != '\0') {
        currentBucket = bucketArray; // When in collision mode, use local array
    }

    // Check magic number at offset +0x06 (struct signature)
    if (*(short*)((int)currentBucket + 6) == 0x25e3) {
        if (*currentBucket != 0) {
            // Return pointer to data: base + offset
            return (int*)(currentBucket[2] + *currentBucket);
        }
        // Return a global null-like pointer
        return &DAT_0120e700;
    }

    // Default: return pointer to start of next entry?
    return currentBucket + 2;
}