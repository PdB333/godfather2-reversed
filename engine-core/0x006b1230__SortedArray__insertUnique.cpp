// FUNC_NAME: SortedArray::insertUnique
uint * __thiscall SortedArray::insertUnique(undefined4 *this, uint *value)
{
  int index;
  uint *currentEntry;
  
  index = 0;
  if (0 < (int)this[1]) { // this[1] = count of elements
    currentEntry = (uint *)*this; // this[0] = array pointer
    do {
      if (*value == *currentEntry) {
        return (uint *)0x0; // duplicate found, return null
      }
      if (*value < *currentEntry) break; // found insertion point
      index = index + 1;
      currentEntry = currentEntry + 2; // each entry is 8 bytes (key + value)
    } while (index < (int)this[1]);
  }
  currentEntry = (uint *)FUN_006b0dc0(index); // allocate/grow array at index
  *currentEntry = *value; // store key
  return currentEntry + 1; // return pointer to value slot
}