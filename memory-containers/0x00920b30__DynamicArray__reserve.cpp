// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  undefined4 *newBuffer;
  uint i;
  undefined4 *destPtr;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4); // allocate memory
    if (*this != 0) {
      i = 0;
      destPtr = newBuffer;
      if (this[1] != 0) {
        do {
          if (destPtr != (undefined4 *)0x0) {
            *destPtr = *(undefined4 *)(*this + i * 4); // copy element
          }
          i = i + 1;
          destPtr = destPtr + 1;
        } while (i < (uint)this[1]); // copy all existing elements
      }
      FUN_009c8f10(*this); // free old buffer
    }
    *this = (int)newBuffer; // +0x00: buffer pointer
    this[2] = newCapacity; // +0x08: capacity
  }
  return;
}