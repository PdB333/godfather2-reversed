// FUNC_NAME: DynamicArray::removeRange
void __thiscall DynamicArray::removeRange(int *this, int startIndex, int endIndex)
{
  int range;
  int newSize;
  int *dst;
  int *src;
  int count;

  range = endIndex - startIndex;
  if (range != 0) {
    // +0x00: pointer to element array, +0x04: number of elements (size)
    newSize = this[1] - range;
    dst = (int *)(this[0] + startIndex * 4);  // start of removal area
    src = (int *)(this[0] + endIndex * 4);    // first element after removal
    if (startIndex < newSize) {
      count = newSize - startIndex;             // number of elements to shift
      do {
        *dst = *src;
        dst++;
        src++;
        count--;
      } while (count != 0);
    }
    this[1] = newSize;                         // update size
  }
}