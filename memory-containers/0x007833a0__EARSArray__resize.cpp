// FUNC_NAME: EARSArray::resize
void __thiscall EARSArray::resize(int *this, uint newCapacity)
{
  int *oldData;
  int iVar2;
  int *newData;
  uint idx;
  int *dstSlot;
  
  if ((uint)this[2] < newCapacity) {
    newData = (int *)FUN_009c8e80(newCapacity * 8);
    if (*this != 0) {
      idx = 0;
      dstSlot = newData;
      if (this[1] != 0) {
        do {
          oldData = (int *)(*this + idx * 8);
          if (dstSlot != (int *)0x0) {
            iVar2 = *oldData;
            *dstSlot = iVar2;
            dstSlot[1] = 0;
            if (iVar2 != 0) {
              dstSlot[1] = *(int *)(iVar2 + 4);
              *(int **)(iVar2 + 4) = dstSlot;
            }
          }
          if (*oldData != 0) {
            FUN_004daf90(oldData);
          }
          idx = idx + 1;
          dstSlot = dstSlot + 2;
        } while (idx < (uint)this[1]);
      }
      FUN_009c8f10(*this);
    }
    *this = (int)newData;
    this[2] = newCapacity;
  }
  return;
}