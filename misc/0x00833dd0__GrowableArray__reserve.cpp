// FUNC_NAME: GrowableArray::reserve
void __thiscall GrowableArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  undefined8 *newData;
  undefined8 *srcPtr;
  int offset;
  uint i;
  
  if ((uint)this[2] < newCapacity) {
    newData = (undefined8 *)FUN_009c8e80(newCapacity * 0xc); // operator new (size = elementSize * count)
    if (*this != 0) {
      i = 0;
      if (this[1] != 0) {
        offset = 0;
        srcPtr = newData;
        do {
          iVar1 = *this;
          if (srcPtr != (undefined8 *)0x0) {
            *srcPtr = *(undefined8 *)(iVar1 + offset); // copy 8 bytes
            *(undefined4 *)(srcPtr + 1) = *(undefined4 *)((undefined8 *)(iVar1 + offset) + 1); // copy remaining 4 bytes
          }
          i = i + 1;
          offset = offset + 0xc; // 12 bytes per element
          srcPtr = (undefined8 *)((int)srcPtr + 0xc);
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this); // operator delete (old buffer)
    }
    *this = (int)newData;
    this[2] = newCapacity; // +0x08: capacity
  }
  return;
}