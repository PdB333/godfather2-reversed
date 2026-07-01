// FUNC_NAME: SomeContainer::shiftElementsDown
void SomeContainer::shiftElementsDown(undefined4 *start, int end, undefined4 param_3)
{
  int elementCount;
  int i;
  undefined4 *src;
  undefined4 *dst;
  undefined4 temp[23]; // 0x5C bytes (0x14 * 4 = 0x50? Actually 23*4=92=0x5C, but used as 0x14*4=80=0x50)
  
  // Calculate number of elements between start and end (each element is 0x50 bytes)
  elementCount = (end - (int)start) / 0x50;
  
  if (1 < elementCount) {
    // Start from the last element before 'end'
    src = (undefined4 *)(end + -0x50);
    do {
      // Copy the current element (0x50 bytes = 0x14 dwords) to temp buffer
      dst = src;
      undefined4 *tempPtr = temp;
      for (i = 0x14; i != 0; i = i + -1) {
        *tempPtr = *dst;
        dst = dst + 1;
        tempPtr = tempPtr + 1;
      }
      
      // Copy the first element to the current position
      dst = src;
      undefined4 *firstPtr = start;
      for (i = 0x14; i != 0; i = i + -1) {
        *dst = *firstPtr;
        firstPtr = firstPtr + 1;
        dst = dst + 1;
      }
      
      // Recursively shift the remaining elements (excluding the first and last)
      FUN_00888890(start, 0, elementCount + -1, 0, temp, param_3);
      
      // Move to the previous element (0x50 bytes = 0x14 dwords)
      src = src + -0x14;
      elementCount = ((0x50 - (int)start) + (int)src) / 0x50;
    } while (1 < elementCount);
  }
  return;
}