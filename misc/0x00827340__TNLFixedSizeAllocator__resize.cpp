// FUNC_NAME: TNLFixedSizeAllocator::resize
void __thiscall TNLFixedSizeAllocator::resize(int *this, uint newCapacity)
{
  int *newBlock;
  int *oldBlock;
  int *piVar3;
  uint i;
  int *newEntry;
  
  if ((uint)this[2] < newCapacity) {
    newBlock = (int *)FUN_009c8e80(newCapacity * 8); // allocate new block array (each entry: pointer + nextFree)
    if (*this != 0) {
      i = 0;
      newEntry = newBlock;
      if (this[1] != 0) {
        do {
          oldBlock = (int *)(*this + i * 8);
          if (newEntry != (int *)0x0) {
            int *ptr = *oldBlock;
            *newEntry = ptr;
            newEntry[1] = 0;
            if (ptr != 0) {
              newEntry[1] = *(int *)(ptr + 4); // copy next pointer from object
              *(int **)(ptr + 4) = newEntry;    // update object's back-pointer to new entry
            }
          }
          if (*oldBlock != 0) {
            FUN_004daf90(oldBlock); // free old block entry
          }
          i = i + 1;
          newEntry = newEntry + 2;
        } while (i < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old block array
    }
    *this = (int)newBlock;
    this[2] = newCapacity;
  }
  return;
}