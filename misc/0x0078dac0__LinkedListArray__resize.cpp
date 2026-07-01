// FUNC_NAME: LinkedListArray::resize
void __thiscall LinkedListArray::resize(int *this, uint newCapacity)
{
  int *newData;
  int objPtr;
  int *newEntry;
  uint i;
  int *oldEntry;

  // Only grow if new capacity is larger than current capacity
  if ((uint)this[2] < newCapacity) {
    // Allocate new array of 8-byte entries (pointer + next)
    newData = (int *)allocate(newCapacity * 8);
    if (this[0] != 0) {
      i = 0;
      newEntry = newData;
      if (this[1] != 0) {
        do {
          // Pointer to old entry (8 bytes each)
          oldEntry = (int *)(this[0] + i * 8);
          if (newEntry != (int *)0x0) {
            // Copy the object pointer
            objPtr = *oldEntry;
            *newEntry = objPtr;
            // Initialize next pointer to 0
            newEntry[1] = 0;
            if (objPtr != 0) {
              // Update the object's "next" pointer to point to this new entry
              newEntry[1] = *(int *)(objPtr + 4);
              *(int **)(objPtr + 4) = newEntry;
            }
          }
          // Release the old entry (likely destroys the node or frees internal data)
          if (*oldEntry != 0) {
            releaseNode(oldEntry);
          }
          i = i + 1;
          newEntry = newEntry + 2;
        } while (i < (uint)this[1]);
      }
      // Free the old array
      deallocate(this[0]);
    }
    // Update this pointer and capacity
    this[0] = (int)newData;
    this[2] = newCapacity;
  }
  return;
}