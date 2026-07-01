// FUNC_NAME: ObjectPool::findAndRemoveMatching
int __thiscall ObjectPool::findAndRemoveMatching(int thisPtr, code *callback, undefined4 userData)
{
  int *bucketPtr;
  int nodeIndex;
  char callbackResult;
  int bucketOffset;
  uint bucketCount;
  
  bucketCount = 0;
  // +0x14: number of buckets
  if (*(int *)(thisPtr + 0x14) == 0) {
    return 0;
  }
  bucketOffset = 0;
  do {
    // +0x1c: pointer to bucket array (each bucket is 0xc bytes)
    // Each bucket has: +0x0: count, +0x4: head node pointer, +0x8: tail node pointer
    for (nodeIndex = *(int *)(*(int *)(thisPtr + 0x1c) + 4 + bucketOffset); nodeIndex != 0;
        nodeIndex = *(int *)(nodeIndex + 4)) {
      callbackResult = (*callback)(nodeIndex, userData);
      if (callbackResult != '\0') {
        if (nodeIndex == 0) {
          return 0;
        }
        bucketOffset = *(int *)(nodeIndex + 8);
        if (bucketOffset != -1) {
          // Remove node from its bucket
          FUN_007ee0e0(nodeIndex);
          // +0x8: bucket index (set to -1 to mark as free)
          *(undefined4 *)(nodeIndex + 8) = 0xffffffff;
          // Decrement bucket count
          bucketPtr = (int *)(*(int *)(thisPtr + 0x1c) + bucketOffset * 0xc);
          *bucketPtr = *bucketPtr + -1;
          // +0x10: total object count
          *(int *)(thisPtr + 0x10) = *(int *)(thisPtr + 0x10) + -1;
        }
        // +0x10: total object count
        if (*(int *)(thisPtr + 0x10) != 0) {
          return nodeIndex;
        }
        // Pool is now empty, call cleanup function
        FUN_004086d0(&DAT_012069c4);
        return nodeIndex;
      }
    }
    bucketCount = bucketCount + 1;
    bucketOffset = bucketOffset + 0xc;
    // +0x14: number of buckets
    if (*(uint *)(thisPtr + 0x14) <= bucketCount) {
      return 0;
    }
  } while( true );
}