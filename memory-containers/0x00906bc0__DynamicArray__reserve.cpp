// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  undefined4 *newBuffer;
  uint i;
  undefined4 *destPtr;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4); // operator new[](size)
    if (*this != 0) {
      i = 0;
      destPtr = newBuffer;
      if (this[1] != 0) {
        do {
          if (destPtr != (undefined4 *)0x0) {
            *destPtr = *(undefined4 *)(*this + i * 4);
          }
          i = i + 1;
          destPtr = destPtr + 1;
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this); // operator delete[](ptr)
    }
    *this = (int)newBuffer;
    this[2] = newCapacity;
  }
  return;
}