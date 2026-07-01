// FUNC_NAME: SortedArray::insertOrFind
uint * __thiscall SortedArray::insertOrFind(undefined4 *this, uint *key)
{
  int index;
  uint *currentEntry;
  
  index = 0;
  if (0 < (int)this[1]) { // +0x04: count
    currentEntry = (uint *)*this; // +0x00: data array
    do {
      if (*key == *currentEntry) {
        return (uint *)0x0; // already exists, return null
      }
      if (*key < *currentEntry) break; // insertion point found
      index = index + 1;
      currentEntry = currentEntry + 0xb; // each entry is 0x2C bytes (11 uint32s)
    } while (index < (int)this[1]);
  }
  // Insert new entry at index
  currentEntry = (uint *)FUN_008d7980(index); // allocate/insert at position
  *currentEntry = *key; // copy key
  return currentEntry + 1; // return pointer to data after key
}