// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  undefined4 *newBuffer;
  uint i;
  undefined4 *dst;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4);
    if (*this != 0) {
      i = 0;
      dst = newBuffer;
      if (this[1] != 0) {
        do {
          if (dst != (undefined4 *)0x0) {
            *dst = *(undefined4 *)(*this + i * 4);
          }
          i = i + 1;
          dst = dst + 1;
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this);
    }
    *this = (int)newBuffer;
    this[2] = newCapacity;
  }
  return;
}