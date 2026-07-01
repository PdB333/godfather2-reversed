// FUNC_NAME: BinarySearchByKey::findEntry
int __thiscall BinarySearchByKey::findEntry(int this, uint key)
{
  int basePtr;
  int count;
  int low;
  int high;
  int mid;
  int result;
  
  basePtr = *(int *)(this + 0x2c);  // +0x2c: pointer to array metadata
  result = 0;
  if (basePtr != 0) {
    count = *(int *)(basePtr + 0xc);  // +0x0c: number of entries
    high = -1;
    if (count != 0) {
      basePtr = *(int *)(basePtr + 0x1c);  // +0x1c: pointer to entry array (each entry 8 bytes)
      low = count;
      do {
        mid = (low + high) >> 1;  // binary search midpoint
        result = mid;
        if (*(uint *)(basePtr + mid * 8) < key) {  // compare first 4 bytes (key) of entry
          result = low;
          high = mid;
        }
        low = result;
      } while (high + 1 != result);  // continue until range narrowed
      if ((result < count) && (*(uint *)(basePtr + result * 8) == key)) {
        result = basePtr + result * 8;  // return pointer to matching entry (8 bytes: 4-byte key + 4-byte value)
      }
    }
  }
  return result;
}