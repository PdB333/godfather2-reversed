// FUNC_NAME: HashTable::rehash
void __thiscall HashTable::rehash(int this, uint newBucketCount)
{
  size_t newSize;
  uint *oldBucket;
  uint hashValue;
  void *newBuckets;
  uint i;
  
  newSize = newBucketCount * 4;
  newBuckets = (void *)FUN_0068ab90(newSize + 4, "EASTL", 0, 0,
                                    "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
  _memset(newBuckets, 0, newSize);
  *(undefined4 *)(newSize + (int)newBuckets) = 0xffffffff; // Sentinel value at end
  i = 0;
  if (*(int *)(this + 8) != 0) { // +0x08: bucketCount
    do {
      oldBucket = *(uint **)(*(int *)(this + 4) + i * 4); // +0x04: buckets array
      while (oldBucket != (uint *)0x0) {
        hashValue = *oldBucket;
        *(uint *)(*(int *)(this + 4) + i * 4) = oldBucket[7]; // oldBucket[7] = next pointer
        oldBucket[7] = *(uint *)((int)newBuckets + (hashValue % newBucketCount) * 4);
        *(uint **)((int)newBuckets + (hashValue % newBucketCount) * 4) = oldBucket;
        oldBucket = *(uint **)(*(int *)(this + 4) + i * 4);
      }
      i = i + 1;
    } while (i < *(uint *)(this + 8));
  }
  if (1 < *(uint *)(this + 8)) {
    FUN_009c8f10(*(undefined4 *)(this + 4)); // Free old bucket array
  }
  *(void **)(this + 4) = newBuckets;
  *(uint *)(this + 8) = newBucketCount;
  return;
}