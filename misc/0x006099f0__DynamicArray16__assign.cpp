// FUNC_NAME: DynamicArray16::assign
int * __thiscall DynamicArray16::assign(int *this, int *other)
{
  int capacity = other[2]; // +0x08 capacity (number of 16-byte slots allocated)
  int newSize = other[1];  // +0x04 current size (number of elements stored)
  this[2] = capacity;      // copy capacity
  this[1] = newSize;       // copy size

  if (capacity != 0) {
    // allocate new buffer: capacity * 16 bytes
    int *newData = (int *)FUN_009c8e80(capacity << 4);
    this[0] = (int)newData; // +0x00 pointer to data

    if (newSize != 0) {
      int srcPtr = other[0]; // source data pointer
      int destOffset = 0;
      for (uint i = 0; i < (uint)newSize; i++) {
        unsigned long long *destSlot = (unsigned long long *)(newData + destOffset);
        if (destSlot != (unsigned long long *)0x0) {
          unsigned long long *srcSlot = (unsigned long long *)(srcPtr + destOffset);
          *destSlot = srcSlot[0];
          destSlot[1] = srcSlot[1];
        }
        destOffset += 4; // each slot is 16 bytes (4 ints)
      }
    }
    return this;
  }
  // capacity 0: set pointer to null
  this[0] = 0;
  return this;
}