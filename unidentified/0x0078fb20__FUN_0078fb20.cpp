// FUNC_NAME: SomeClass::findIndexForValue
uint __thiscall findIndexForValue(int this, int value)
{
  uint index;
  uint count;
  uint i;
  int *arrayPtr;
  
  index = 0;
  // If value is <= the first element (at +0x54), return last index (count-1)
  if (value <= *(int *)(this + 0x54)) {
    return *(int *)(this + 0x94) - 1;
  }
  // If there are more than 1 elements, search the array at +0x5c
  if (1 < *(uint *)(this + 0x94)) {
    arrayPtr = (int *)(this + 0x5c);
    index = 0;
    do {
      index = index; // no-op, just loop counter
      if (value <= *arrayPtr) {
        return index;
      }
      arrayPtr = arrayPtr + 2; // each element is 8 bytes (2 ints)
      index = index + 1;
    } while (index < *(uint *)(this + 0x94));
  }
  return index;
}