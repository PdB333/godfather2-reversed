// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int thisPtr, undefined4 value)
{
  undefined4 *elementPtr;
  int currentSize;
  
  currentSize = *(int *)(thisPtr + 0x18); // +0x18: capacity (max elements)
  if (*(int *)(thisPtr + 0x14) == currentSize) { // +0x14: current element count
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2;
    }
    // Grow the array to new capacity
    FUN_0080ff20(currentSize); // likely reallocate/grow internal buffer
  }
  // Calculate pointer to next slot in the array
  elementPtr = (undefined4 *)(*(int *)(thisPtr + 0x10) + *(int *)(thisPtr + 0x14) * 4); // +0x10: data buffer pointer
  // Increment element count
  *(int *)(thisPtr + 0x14) = *(int *)(thisPtr + 0x14) + 1;
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = value; // Store the new element
  }
  return;
}