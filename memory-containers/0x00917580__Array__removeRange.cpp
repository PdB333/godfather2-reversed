// FUNC_NAME: Array::removeRange
void __thiscall Array::removeRange(int *this, int startIndex, int endIndex)
{
  int newSize;
  undefined4 *srcPtr;
  undefined4 *dstPtr;
  
  if (endIndex - startIndex != 0) {
    newSize = this[1] - (endIndex - startIndex);
    dstPtr = (undefined4 *)(*this + startIndex * 4);
    srcPtr = (undefined4 *)(*this + endIndex * 4);
    if (startIndex < newSize) {
      startIndex = newSize - startIndex;
      do {
        *dstPtr = *srcPtr;
        srcPtr = srcPtr + 1;
        dstPtr = dstPtr + 1;
        startIndex = startIndex + -1;
      } while (startIndex != 0);
    }
    this[1] = newSize; // update element count
  }
  return;
}