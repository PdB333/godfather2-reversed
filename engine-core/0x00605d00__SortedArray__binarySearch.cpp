// FUNC_NAME: SortedArray::binarySearch
int SortedArray::binarySearch(int *outIndex)
{
  int low = 0;
  int high = *(int *)(this + 0x10) - 1; // +0x10: element count
  if (high < 0) {
    return 0;
  }
  do {
    int mid = (high + low) / 2;
    uint midValue = *(uint *)(*(int *)(this + 0x18) + mid * 4); // +0x18: array pointer
    if (unaff_EDI == midValue) {
      *outIndex = mid;
      return 1;
    }
    if (unaff_EDI < midValue) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  } while (low <= high);
  return 0;
}