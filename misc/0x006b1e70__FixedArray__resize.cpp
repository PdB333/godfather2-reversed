// FUNC_NAME: FixedArray::resize
void __thiscall FixedArray::resize(int *this, uint newCapacity)
{
  int *newBuffer;
  int *srcSlot;
  int *dstSlot;
  uint i;
  int *srcSlot2;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (int *)FUN_009c8e80(newCapacity * 8);
    if (*this != 0) {
      i = 0;
      dstSlot = newBuffer;
      if (this[1] != 0) {
        do {
          srcSlot = (int *)(*this + i * 8);
          if (dstSlot != (int *)0x0) {
            int value = *srcSlot;
            *dstSlot = value;
            dstSlot[1] = 0;
            if (value != 0) {
              dstSlot[1] = *(int *)(value + 4);
              *(int **)(value + 4) = dstSlot;
            }
          }
          if (*srcSlot != 0) {
            FUN_004daf90(srcSlot);
          }
          i = i + 1;
          dstSlot = dstSlot + 2;
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this);
    }
    *this = (int)newBuffer;
    this[2] = newCapacity;
  }
  return;
}