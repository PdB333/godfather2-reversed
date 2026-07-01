// FUNC_NAME: GrowableArray::resize
void __thiscall GrowableArray::resize(int *this, uint newCapacity)
{
  int *newData;
  int iVar2;
  int *piVar3;
  uint idx;
  int *srcPtr;
  
  if ((uint)this[2] < newCapacity) {
    piVar3 = (int *)FUN_009c8e80(newCapacity * 8); // allocate new array of pairs (8 bytes each)
    if (*this != 0) {
      idx = 0;
      srcPtr = piVar3;
      if (this[1] != 0) {
        do {
          int *oldEntry = (int *)(*this + idx * 8);
          if (srcPtr != (int *)0x0) {
            int val = *oldEntry;
            *srcPtr = val;
            srcPtr[1] = 0;
            if (val != 0) {
              srcPtr[1] = *(int *)(val + 4); // copy linked list next pointer
              *(int **)(val + 4) = srcPtr; // update back pointer
            }
          }
          if (*oldEntry != 0) {
            FUN_004daf90(oldEntry); // destroy old element
          }
          idx = idx + 1;
          srcPtr = srcPtr + 2;
        } while (idx < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old array
    }
    *this = (int)piVar3;
    this[2] = newCapacity;
  }
  return;
}