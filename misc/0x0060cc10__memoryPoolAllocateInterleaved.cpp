// FUNC_NAME: memoryPoolAllocateInterleaved
void memoryPoolAllocateInterleaved(int elementSize, uint count, void *srcData, size_t stride)
{
  void *poolBlock;
  void *destPtr;
  
  if (elementSize == 0xd) {
    // Special case for 13-byte elements
    if (count != 4) {
      // Interleaved copy: count/2 groups of 6 elements, each group interleaved from source
      // Reinterprets source as blocks of stride*4 bytes, interleaves within each block
      uint blocks = count >> 2;  // Number of 4-element blocks
      poolBlock = (void *)memoryPoolAllocate(4, blocks * 6, 0, 1, 0); // +0x60cd00: pool alloc with alignment flags
      if (poolBlock == (void *)0x0) {
        return;
      }
      for (; blocks != 0; blocks = blocks - 1) {
        // Interleave pattern for each block of 4 source elements:
        // dest[0] = src[0] (stride bytes)
        _memcpy(poolBlock, srcData, stride);
        // dest[1] = src[1]
        _memcpy((void *)((int)poolBlock + stride), (void *)((int)srcData + stride), stride);
        // dest[2] = src[2]
        void *src2 = (void *)((int)srcData + stride * 2);
        destPtr = (void *)((int)((int)poolBlock + stride) + stride);
        _memcpy(destPtr, src2, stride);
        destPtr = (void *)((int)destPtr + stride);
        // dest[3] = src[0] again
        _memcpy(destPtr, srcData, stride);
        destPtr = (void *)((int)destPtr + stride);
        // dest[4] = src[2]
        _memcpy(destPtr, src2, stride);
        destPtr = (void *)((int)destPtr + stride);
        // dest[5] = src[3]
        _memcpy(destPtr, (void *)(stride * 3 + (int)srcData), stride);
        destPtr = (void *)((int)destPtr + stride);
        srcData = (void *)((int)srcData + stride * 4);
      }
      memoryPoolFree(); // +0x60cde0: release pool lock/commit
      return;
    }
    elementSize = 6;  // 4-element case: treat as 6 bytes
  }
  // Standard allocation and copy
  poolBlock = (void *)memoryPoolAllocate(elementSize, count, 0, 1, 0);
  if (poolBlock == (void *)0x0) {
    return;
  }
  _memcpy(poolBlock, srcData, count * stride);
  memoryPoolFree();
  return;
}