// FUNC_NAME: GrowableArray::reserve
void __thiscall GrowableArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  int *newData;
  int *srcPtr;
  int *dstPtr;
  int offset;
  uint idx;
  int *oldData;
  
  if ((uint)this[2] < newCapacity) {
    newData = (int *)FUN_009c8e80(newCapacity * 0xc); // allocate 12 bytes per element
    if (*this != 0) {
      idx = 0;
      if (this[1] != 0) {
        offset = 0;
        dstPtr = newData;
        do {
          srcPtr = (int *)(*this + offset);
          if (dstPtr != (int *)0x0) {
            iVar1 = *srcPtr;
            *dstPtr = iVar1;
            dstPtr[1] = 0;
            if (iVar1 != 0) {
              dstPtr[1] = *(int *)(iVar1 + 4); // +0x4: next pointer in linked list
              *(int **)(iVar1 + 4) = dstPtr;    // update back pointer
            }
            dstPtr[2] = srcPtr[2]; // copy third field (likely size or flags)
          }
          if (*srcPtr != 0) {
            FUN_004daf90(srcPtr); // destructor or cleanup for element
          }
          idx = idx + 1;
          offset = offset + 0xc;
          dstPtr = dstPtr + 3;
        } while (idx < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old array
    }
    *this = (int)newData;
    this[2] = newCapacity;
  }
  return;
}