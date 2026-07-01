// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  undefined4 *newBuffer;
  uint i;
  undefined4 *dst;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 8); // operator new[](size)
    if (*this != 0) {
      i = 0;
      dst = newBuffer;
      if (this[1] != 0) {
        do {
          if (dst != (undefined4 *)0x0) {
            iVar1 = *this;
            *dst = *(undefined4 *)(iVar1 + i * 8);      // copy first 4 bytes of element
            dst[1] = *(undefined4 *)(iVar1 + 4 + i * 8); // copy second 4 bytes of element
          }
          i = i + 1;
          dst = dst + 2;
        } while (i < (uint)this[1]); // while i < count
      }
      FUN_009c8f10(*this); // operator delete[](oldBuffer)
    }
    *this = (int)newBuffer;
    this[2] = newCapacity; // capacity
  }
  return;
}