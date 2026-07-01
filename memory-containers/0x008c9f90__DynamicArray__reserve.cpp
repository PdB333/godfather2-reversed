// FUNC_NAME: DynamicArray::reserve
// Address: 0x008c9f90
// Role: Reserves capacity in a dynamic array (reallocates if needed). The structure has:
//   +0x00: int* mData (pointer to allocated buffer)
//   +0x04: uint mCount (number of stored elements)
//   +0x08: uint mCapacity (allocated capacity in elements)
// Called when new capacity is greater than current capacity.

void __thiscall DynamicArray::reserve(int* this_, uint newCapacity)
{
  uint* pvNewBuffer;
  uint oldCount;
  uint* pvNewIter;

  if ((uint)this_[2] < newCapacity) {
    // Allocate new buffer (each element is 4 bytes)
    pvNewBuffer = (uint*)FUN_009c8e80(newCapacity * 4);
    if (this_[0] != 0) {
      oldCount = 0;
      pvNewIter = pvNewBuffer;
      if (this_[1] != 0) {
        do {
          // Copy each element from old buffer to new buffer
          if (pvNewIter != (uint*)0x0) {
            *pvNewIter = *(uint*)(this_[0] + oldCount * 4);
          }
          oldCount = oldCount + 1;
          pvNewIter = pvNewIter + 1;
        } while (oldCount < (uint)this_[1]);
      }
      // Free old buffer
      FUN_009c8f10(this_[0]);
    }
    // Update pointers and capacity
    this_[0] = (int)pvNewBuffer;
    this_[2] = newCapacity;
  }
  return;
}