// FUNC_NAME: quickSortPartition
void quickSortPartition(uint *start, uint *end)
{
  uint *pivot;
  int i;
  int j;
  uint *left;
  uint *right;
  uint *store;
  uint temp[23]; // 0x5C bytes (0x14 * 4 + 3 padding)
  
  if (start != end) {
    do {
      left = start;
      pivot = temp;
      for (i = 0x14; i != 0; i = i + -1) {
        *pivot = *left;
        left = left + 1;
        pivot = pivot + 1;
      }
      
      left = start + -0x12; // start - 18 (0x12)
      pivot = start;
      
      if (temp[2] < start[-0x12]) {
        i = (int)left + (-8 - (int)start); // offset calculation
        do {
          right = (uint *)(i + (int)pivot);
          store = pivot;
          for (j = 0x14; j != 0; j = j + -1) {
            *store = *right;
            right = right + 1;
            store = store + 1;
          }
          left = left + -0x14; // move left by 20 (0x14)
          pivot = pivot + -0x14; // move pivot by 20
        } while (temp[2] < *left);
      }
      
      start = start + 0x14; // advance start by 20
      left = temp;
      for (i = 0x14; i != 0; i = i + -1) {
        *pivot = *left;
        left = left + 1;
        pivot = pivot + 1;
      }
    } while (start != end);
  }
  return;
}