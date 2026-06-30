// FUNC_NAME: BucketArray::init
void BucketArray::init(int sizeIndex, MemoryAllocator* alloc)
{
    int numEntries = 1 << (sizeIndex & 0x1f);
    if (sizeIndex > 24) {
        alloc->error("table overflow");
    }
    if (sizeIndex == 0) {
        // Use pre-allocated static buffer from allocator
        char* base = *(char**)(alloc + 0x10); // +0x10: base of static buffer
        this->bucketType = (byte)sizeIndex;        // +0x07
        this->bucketBuffer = base + 0x40;          // +0x10: pointer to first bucket
        this->bucketEnd   = base + 0x2c + numEntries * 0x14; // +0x14: pointer past last bucket
        return;
    }
    uint allocSize = numEntries * 0x14;
    char* newBuffer = alloc->allocate(0, allocSize);
    if (newBuffer == 0) {
        if (alloc != 0) {
            alloc->handleAllocFailure();
            return;
        }
        newBuffer = 0;
    } else if (alloc != 0) {
        // Update allocation counter
        int* counter = *(int**)(alloc + 0x10) + 0x24; // +0x10: base, +0x24: allocation counter
        *counter += allocSize;
    }
    this->bucketBuffer = newBuffer; // +0x10
    // Zero out all buckets (each 0x14 bytes, with fields at offsets 0, 8, 0x10)
    if (numEntries > 0) {
        for (int i = 0; i < numEntries; i++) {
            char* bucket = this->bucketBuffer + i * 0x14;
            *(int*)(bucket + 0)  = 0;
            *(int*)(bucket + 8)  = 0;
            *(int*)(bucket + 16) = 0;
        }
    }
    this->bucketType = (byte)sizeIndex;                       // +0x07
    this->bucketEnd = this->bucketBuffer + (numEntries - 1) * 0x14; // +0x14
}