// FUNC_NAME: binarySearchByKey
int binarySearchByKey(int base, int end, byte *key)
{
  int count;
  int half;
  
  count = (end - base) >> 3;
  if (0 < count) {
    do {
      half = count / 2;
      if (*(byte *)(base + half * 8) < *key) {
        base = base + 8 + half * 8;
        half = count + (-1 - half);
      }
      count = half;
    } while (0 < half);
  }
  return base;
}