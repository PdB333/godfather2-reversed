// FUNC_NAME: FixedArray::reserve
void __thiscall FixedArray::reserve(int *this, uint newCapacity)
{
  int *newData;
  int *srcPtr;
  int *dstPtr;
  int i;
  uint idx;
  int *oldData;
  
  if ((uint)this[2] < newCapacity) {
    newData = (int *)FUN_009c8e80(newCapacity * 0xc); // allocate 12 bytes per element
    if (*this != 0) {
      idx = 0;
      if (this[1] != 0) {
        i = 0;
        dstPtr = newData;
        do {
          srcPtr = (int *)(*this + i);
          if (dstPtr != (int *)0x0) {
            // Copy element data (first int is value, second is linked list prev, third is next)
            int val = *srcPtr;
            *dstPtr = val;
            dstPtr[1] = 0;
            if (val != 0) {
              dstPtr[1] = *(int *)(val + 4); // link to previous element
              *(int **)(val + 4) = dstPtr;    // update previous element's next pointer
            }
            dstPtr[2] = srcPtr[2]; // copy third field
          }
          if (*srcPtr != 0) {
            FUN_004daf90(srcPtr); // destructor for element
          }
          idx = idx + 1;
          i = i + 0xc;
          dstPtr = dstPtr + 3;
        } while (idx < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old data
    }
    *this = (int)newData;
    this[2] = newCapacity;
  }
  return;
}