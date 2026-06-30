// FUNC_NAME: SortedArray::insertUnique
uint * __thiscall SortedArray::insertUnique(uint *this, uint *value)
{
  int index;
  uint *current;
  
  index = 0;
  if (0 < (int)this[1]) { // this[1] = count of elements
    current = (uint *)*this; // this[0] = pointer to array data
    do {
      if (*value == *current) {
        return (uint *)0x0; // duplicate found, return null
      }
      if (*value < *current) break; // insertion point found
      index = index + 1;
      current = current + 2; // each element is 8 bytes (uint key + uint value)
    } while (index < (int)this[1]);
  }
  // Insert new element at position 'index'
  current = (uint *)FUN_006b0e40(index); // allocate/grow array and shift elements
  *current = *value; // store key
  return current + 1; // return pointer to value slot
}