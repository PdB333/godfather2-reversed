// FUNC_NAME: FixedArray::resize
void __thiscall FixedArray::resize(int *this, uint newCapacity)
{
  int *newBuffer;
  int *srcPtr;
  int *dstPtr;
  uint i;
  int *oldBuffer;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (int *)FUN_009c8e80(newCapacity * 8); // allocate new buffer (8 bytes per element: pointer + ref count)
    if (*this != 0) {
      i = 0;
      dstPtr = newBuffer;
      if (this[1] != 0) {
        do {
          srcPtr = (int *)(*this + i * 8);
          if (dstPtr != (int *)0x0) {
            int *elem = *srcPtr;
            *dstPtr = elem;
            dstPtr[1] = 0;
            if (elem != 0) {
              dstPtr[1] = *(int *)(elem + 4); // copy reference count from element
              *(int **)(elem + 4) = dstPtr; // update element's back pointer
            }
          }
          if (*srcPtr != 0) {
            FUN_004daf90(srcPtr); // release old element reference
          }
          i = i + 1;
          dstPtr = dstPtr + 2;
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old buffer
    }
    *this = (int)newBuffer;
    this[2] = newCapacity;
  }
  return;
}