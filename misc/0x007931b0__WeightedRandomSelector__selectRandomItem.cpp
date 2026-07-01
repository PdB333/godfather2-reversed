// FUNC_NAME: WeightedRandomSelector::selectRandomItem
undefined4 __thiscall WeightedRandomSelector::selectRandomItem(int this, undefined4 *outResult)
{
  uint randVal;
  int i;
  undefined4 result;
  int *weightPtr;
  uint cumulativeWeight;
  
  *outResult = 0;
  randVal = _rand();
  cumulativeWeight = 0;
  i = 0;
  weightPtr = (int *)(this + 0x60); // +0x60: array of 4 weights (each 7 ints stride)
  do {
    cumulativeWeight = cumulativeWeight + *weightPtr;
    if (randVal % *(uint *)(this + 0xc0) < cumulativeWeight) { // +0xC0: total weight sum
      result = FUN_007930f0(i, outResult); // get item at index i
      return result;
    }
    i = i + 1;
    weightPtr = weightPtr + 7; // stride of 7 ints per entry (weight + 6 other fields)
  } while (i < 4);
  return 0;
}