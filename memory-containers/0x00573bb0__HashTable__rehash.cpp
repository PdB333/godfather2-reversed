// FUNC_NAME: HashTable::rehash
void HashTable::rehash(int *this)
{
  int *oldBuckets;
  uint newSize;
  uint *bucket;
  uint *nextBucket;
  int *bucketPtr;
  void *newBuckets;
  
  bucketPtr = this;
  newSize = this[1] * 2 + 1;
  newBuckets = (void *)FUN_009c8e80(-(uint)((int)((ulonglong)newSize * 4 >> 0x20) != 0) |
                              (uint)((ulonglong)newSize * 4));
  _memset(newBuckets, 0, newSize * 4);
  oldBuckets = this + 1;
  this = (int *)0x0;
  if (*oldBuckets != 0) {
    do {
      bucket = *(uint **)(*bucketPtr + (int)this * 4);
      while (bucket != (uint *)0x0) {
        nextBucket = (uint *)bucket[3];
        bucket[3] = *(uint *)((int)newBuckets + (*bucket % newSize) * 4);
        *(uint **)((int)newBuckets + (*bucket % newSize) * 4) = bucket;
        bucket = nextBucket;
      }
      this = (int *)((int)this + 1);
    } while (this < (uint)bucketPtr[1]);
  }
  FUN_009c8f10(*bucketPtr);
  *bucketPtr = (int)newBuckets;
  bucketPtr[1] = newSize;
  return;
}