// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  undefined8 *newBuffer;
  undefined8 *srcPtr;
  int iVar4;
  uint uVar5;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined8 *)FUN_009c8e80(newCapacity << 4); // allocate 16 bytes per element
    if (*this != 0) {
      uVar5 = 0;
      if (this[1] != 0) {
        iVar4 = 0;
        srcPtr = newBuffer;
        do {
          iVar1 = *this;
          if (srcPtr != (undefined8 *)0x0) {
            *srcPtr = *(undefined8 *)(iVar1 + iVar4);
            srcPtr[1] = ((undefined8 *)(iVar1 + iVar4))[1];
          }
          uVar5 = uVar5 + 1;
          iVar4 = iVar4 + 0x10;
          srcPtr = srcPtr + 2;
        } while (uVar5 < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old buffer
    }
    *this = (int)newBuffer;
    this[2] = newCapacity;
  }
  return;
}