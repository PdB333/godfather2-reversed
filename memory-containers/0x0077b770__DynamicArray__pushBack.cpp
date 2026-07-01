// FUNC_NAME: DynamicArray::pushBack

void __thiscall DynamicArray::pushBack(int *thisPtr, undefined4 *valuePtr)
{
  int size = thisPtr[1];  // offset +0x04
  int capacity = thisPtr[2]; // offset +0x08

  if (size == capacity) {
    // Need to grow: if capacity zero, set to 1; else double
    int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
    FUN_0077b420(newCapacity); // Resize internal buffer (realloc or alloc)
  }

  // Write value at end of array
  undefined4 *dest = (undefined4 *)(thisPtr[0] + size * 4); // offset +0x00 points to data buffer
  thisPtr[1] = size + 1;
  if (dest != (undefined4 *)0x0) {
    *dest = *valuePtr;
  }
}