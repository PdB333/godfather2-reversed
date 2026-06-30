// FUNC_NAME: Sorted128Array::FindIndex
int __thiscall Sorted128Array::FindIndex(int *this, uint *key)
{
  int *arrayBase;
  int count;
  int low;
  int high;
  int mid;
  uint elem3;
  uint elem2;
  uint *elementPtr;
  uint key2, key3;
  uint k0, k1, k2, k3;

  count = this[1];                               // +0x04: number of elements
  low = -1;
  if (count != 0)
  {
    arrayBase = (int *)this[0];                  // +0x00: pointer to array
    k2 = key[2];
    k3 = key[3];
    high = count;
    do
    {
      mid = (high + low) >> 1;
      elem3 = *(uint *)((int)arrayBase + 0xc + mid * 0x18); // element[3] at offset 0x0C
      elem2 = *(uint *)((int)arrayBase + 8 + mid * 0x18);  // element[2] at offset 0x08
      elementPtr = (uint *)((int)arrayBase + mid * 0x18); // base pointer to element

      // Lexicographic comparison: check if element < key
      if ((elem3 < k3) ||
          ((elem3 <= k3) && (elem2 < k2)) ||
          ((elem2 == k2) &&
           ((elem3 == k3 && (elem3 = elementPtr[1], elem3 <= key[1])) &&
            ((elem3 < key[1]) || (*elementPtr < key[0])))))
      {
        low = mid;
        mid = high;
      }
      high = mid;
    } while (low + 1 != high);

    // Check exact match
    if ((mid < count) &&
        (elementPtr = (uint *)((int)arrayBase + mid * 0x18),
         (elementPtr[2] == k2) &&
         (elementPtr[3] == k3) &&
         (*elementPtr == key[0]) &&
         (elementPtr[1] == key[1])))
    {
      return mid;
    }
  }
  return -1;
}