// FUNC_NAME: ResourceManager::duplicateBatch
void __thiscall duplicateBatch(undefined4 *batchOut, undefined4 *sourceStart, undefined4 *sourceEnd, undefined4 *batchElements)
{
  int elementSize;
  undefined4 *sourcePtr;
  undefined4 *destPtr;
  
  *batchOut = batchElements;  // Initialize output array pointer
  
  if (sourceStart != sourceEnd) {
    do {
      if (batchElements != (undefined4 *)0x0) {
        sourcePtr = sourceStart;
        destPtr = batchElements;
        // Copy 0x141 dwords = 0x504 bytes per element (standard EA batch element size)
        for (elementSize = 0x141; elementSize != 0; elementSize = elementSize + -1) {
          *destPtr = *sourcePtr;
          sourcePtr = sourcePtr + 1;
          destPtr = destPtr + 1;
        }
      }
      sourceStart = sourceStart + 0x141;  // Advance source by element size
      batchElements = batchElements + 0x141;  // Advance dest by element size
    } while (sourceStart != sourceEnd);  // Continue until all elements copied
    *batchOut = batchElements;  // Update output pointer to end of copied data
  }
  return;
}