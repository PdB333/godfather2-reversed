// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(int *this, uint newCapacity)
{
  int *oldData;
  int *srcPtr;
  undefined4 *newData;
  int i;
  undefined4 *dstPtr;
  undefined4 *srcElement;
  
  oldData = this;
  if ((uint)this[2] < newCapacity) {
    newData = (undefined4 *)FUN_009c8e80(newCapacity * 0x14); // allocate new array (element size 0x14)
    i = 0;
    if (*this != 0) {
      srcPtr = this + 1;
      this = (int *)0x0;
      dstPtr = newData;
      if (*srcPtr != 0) {
        do {
          srcElement = (undefined4 *)(*oldData + i);
          if (dstPtr != (undefined4 *)0x0) {
            *dstPtr = *srcElement;
            dstPtr[1] = srcElement[1];
            FUN_006099f0(srcElement + 2); // copy constructor for element at offset +8
          }
          if (srcElement[2] != 0) {
            FUN_009c8f10(srcElement[2]); // free old element's internal data
          }
          this = (int *)((int)this + 1);
          i = i + 0x14;
          dstPtr = dstPtr + 5;
        } while (this < (uint)oldData[1]);
      }
      FUN_009c8f10(*oldData); // free old array buffer
    }
    *oldData = (int)newData;
    oldData[2] = newCapacity;
  }
  return;
}