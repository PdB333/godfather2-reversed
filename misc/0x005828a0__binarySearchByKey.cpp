// FUNC_NAME: binarySearchByKey
int binarySearchByKey(uint key, int* array, int count)
{
  int low = -1;
  int high = count;
  
  if (count == 0) {
    return -1;
  }
  
  do {
    int mid = (high + low) >> 1;
    int current = mid;
    
    if (*(uint*)(array + mid * 0x14) < key) {
      current = high;
      low = mid;
    }
    
    high = current;
  } while (low + 1 != current);
  
  // Check if the found element matches the key
  if ((current < count) &&
      (uint foundKey = *(uint*)(array + current * 0x14), key > foundKey || foundKey == key) &&
      (key <= foundKey)) {
    return current;
  }
  
  return -1;
}