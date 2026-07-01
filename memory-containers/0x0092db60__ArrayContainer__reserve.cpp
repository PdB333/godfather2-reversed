// FUNC_NAME: ArrayContainer::reserve
void __thiscall ArrayContainer::reserve(int *this, uint newCapacity)
{
  undefined4 *newBuffer;
  uint idx;
  undefined4 *dstPtr;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4); // malloc/new
    if (*this != 0) {
      idx = 0;
      dstPtr = newBuffer;
      if (this[1] != 0) {
        do {
          if (dstPtr != (undefined4 *)0x0) {
            *dstPtr = *(undefined4 *)(*this + idx * 4);
          }
          idx = idx + 1;
          dstPtr = dstPtr + 1;
        } while (idx < (uint)this[1]); // copy existing elements
      }
      FUN_009c8f10(*this); // free(old buffer)
    }
    *this = (int)newBuffer;     // +0x00: buffer pointer
    this[2] = newCapacity;      // +0x08: allocated capacity
  }
  return;
}