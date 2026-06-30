// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
  int iVar1;
  undefined4 *newData;
  uint i;
  undefined4 *srcPtr;
  int *thisPtr; // unaff_ESI
  
  if ((uint)thisPtr[2] < newCapacity) {
    newData = (undefined4 *)FUN_009c8e80(newCapacity * 8); // allocate new array (8 bytes per element)
    if (*thisPtr != 0) {
      i = 0;
      srcPtr = newData;
      if (thisPtr[1] != 0) {
        do {
          if (srcPtr != (undefined4 *)0x0) {
            iVar1 = *thisPtr;
            *srcPtr = *(undefined4 *)(iVar1 + i * 8);
            srcPtr[1] = *(undefined4 *)(iVar1 + 4 + i * 8);
          }
          i = i + 1;
          srcPtr = srcPtr + 2;
        } while (i < (uint)thisPtr[1]);
      }
      FUN_009c8f10(*thisPtr); // free old array
    }
    *thisPtr = (int)newData;
    thisPtr[2] = newCapacity;
  }
  return;
}