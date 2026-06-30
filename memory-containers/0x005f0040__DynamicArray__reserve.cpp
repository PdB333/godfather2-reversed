// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
  int iVar1;
  undefined8 *newBuffer;
  undefined8 *srcPtr;
  int iVar4;
  int *thisPtr; // unaff_ESI
  uint uVar5;
  
  if ((uint)thisPtr[2] < newCapacity) {
    newBuffer = (undefined8 *)FUN_009c8e80(newCapacity * 0xc); // operator new(size * elementSize)
    if (*thisPtr != 0) {
      uVar5 = 0;
      if (thisPtr[1] != 0) {
        iVar4 = 0;
        srcPtr = newBuffer;
        do {
          iVar1 = *thisPtr; // old buffer
          if (srcPtr != (undefined8 *)0x0) {
            *srcPtr = *(undefined8 *)(iVar1 + iVar4); // copy 8 bytes
            *(undefined4 *)(srcPtr + 1) = *(undefined4 *)((undefined8 *)(iVar1 + iVar4) + 1); // copy remaining 4 bytes
          }
          uVar5 = uVar5 + 1;
          iVar4 = iVar4 + 0xc; // 12 bytes per element
          srcPtr = (undefined8 *)((int)srcPtr + 0xc);
        } while (uVar5 < (uint)thisPtr[1]); // copy count = current size
      }
      FUN_009c8f10(*thisPtr); // operator delete(old buffer)
    }
    *thisPtr = (int)newBuffer;
    thisPtr[2] = newCapacity; // update capacity
  }
  return;
}