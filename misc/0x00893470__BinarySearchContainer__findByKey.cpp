// FUNC_NAME: BinarySearchContainer::findByKey
int __thiscall BinarySearchContainer::findByKey(int this, uint key)
{
  int *basePtr;
  int count;
  int low;
  int mid;
  int high;
  int result;
  
  basePtr = *(int **)(this + 0x2c);
  if (basePtr != 0) {
    count = *(int *)(basePtr + 8);       // +0x08: element count
    high = -1;
    if (count != 0) {
      basePtr = *(int **)(basePtr + 0x18); // +0x18: array of 0x14-byte elements
      low = count;
      do {
        mid = (low + high) >> 1;
        result = mid;
        if (*(uint *)(basePtr + mid * 0x14) < key) { // first 4 bytes = key field
          result = low;
          high = mid;
        }
        low = result;
      } while (high + 1 != result);
      if ((result < count) && (*(uint *)(basePtr + result * 0x14) == key)) {
        return (int)(basePtr + result * 0x14); // return pointer to element
      }
    }
  }
  return 0;
}