// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  undefined4 *newData;
  uint i;
  undefined4 *dst;
  
  if ((uint)this[2] < newCapacity) {
    newData = (undefined4 *)FUN_009c8e80(newCapacity * 8); // allocate new array (8 bytes per element)
    if (*this != 0) {
      i = 0;
      dst = newData;
      if (this[1] != 0) {
        do {
          if (dst != (undefined4 *)0x0) {
            iVar1 = *this;
            *dst = *(undefined4 *)(iVar1 + i * 8);          // copy first 4 bytes
            dst[1] = *(undefined4 *)(iVar1 + 4 + i * 8);    // copy second 4 bytes
          }
          i = i + 1;
          dst = dst + 2;
        } while (i < (uint)this[1]); // copy existing elements
      }
      FUN_009c8f10(*this); // free old array
    }
    *this = (int)newData;
    this[2] = newCapacity; // update capacity
  }
  return;
}