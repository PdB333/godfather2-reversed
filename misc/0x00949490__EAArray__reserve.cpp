// FUNC_NAME: EAArray::reserve
void __thiscall EAArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  undefined4 *newBuffer;
  uint i;
  undefined4 *destPtr;
  
  if ((uint)this[2] < newCapacity) {
    // Allocate new buffer: each element is 8 bytes (two ints)
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 8);
    if (*this != 0) {
      i = 0;
      destPtr = newBuffer;
      if (this[1] != 0) {
        do {
          if (destPtr != (undefined4 *)0x0) {
            // Copy element: two 4-byte fields
            iVar1 = *this;
            *destPtr = *(undefined4 *)(iVar1 + i * 8);
            destPtr[1] = *(undefined4 *)(iVar1 + 4 + i * 8);
          }
          i = i + 1;
          destPtr = destPtr + 2;
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this); // Free old buffer
    }
    *this = (int)newBuffer;
    this[2] = newCapacity;
  }
  return;
}