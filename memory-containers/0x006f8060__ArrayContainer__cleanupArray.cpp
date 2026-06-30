// FUNC_NAME: ArrayContainer::cleanupArray
void __thiscall ArrayContainer::cleanupArray(int *this)
{
  int i;
  int count;
  
  count = this[1] - 1; // +4 offset: count of elements
  if (count >= 0) {
    do {
      // Each element is 12 bytes (3 ints)
      if (*(int *)(*this + count * 0xc) != 0) {
        // Call destructor/release on the element if its first field (pointer) is non-null
        FUN_004daf90(*this + count * 0xc);
      }
      count = count - 1;
    } while (count >= 0);
  }
  this[1] = 0; // Reset count
  FUN_009c8f10(*this); // Free the array memory
  *this = 0; // Null pointer
  this[2] = 0; // +8 offset: capacity (or other metadata)
}