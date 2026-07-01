// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  undefined4 *newData;
  uint i;
  undefined4 *dest;
  
  if ((uint)this[2] < newCapacity) {
    newData = (undefined4 *)FUN_009c8e80(newCapacity * 4); // operator new[] or malloc
    if (*this != 0) {
      i = 0;
      dest = newData;
      if (this[1] != 0) {
        do {
          if (dest != (undefined4 *)0x0) {
            *dest = *(undefined4 *)(*this + i * 4); // copy element
          }
          i = i + 1;
          dest = dest + 1;
        } while (i < (uint)this[1]); // copy up to current size
      }
      FUN_009c8f10(*this); // free old array
    }
    *this = (int)newData; // +0x00: data pointer
    this[2] = newCapacity; // +0x08: capacity
  }
  return;
}