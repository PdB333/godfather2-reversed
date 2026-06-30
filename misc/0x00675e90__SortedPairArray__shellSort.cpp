// FUNC_NAME: SortedPairArray::shellSort

void SortedPairArray::shellSort(int count)
{
  int gap = count / 2;
  do {
    if (gap < 1) return;
    if (gap < count) {
      // For each element from gap to count-1, perform insertion sort with gap
      for (int i = gap; i < count; i++) {
        // Compare and swap elements at indices j and j-gap while key at j is smaller
        int j = i;
        while (j >= gap) {
          // Compare keys (uint at offset 0) of the two 8-byte pairs
          if (pairs[j].key < pairs[j - gap].key) {
            swap(pairs[j], pairs[j - gap]);
            j -= gap;
          } else {
            break;
          }
        }
      }
    }
    gap /= 2;
  } while (true);
}