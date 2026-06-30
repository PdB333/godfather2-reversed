// FUNC_NAME: Array12::removeAt

// Removes element at index 'param_2' from a dynamic array of 12-byte structures.
// Offset +0x00: pointer to start of array (int*)
// Offset +0x04: current count of elements (unsigned int)
void __thiscall Array12::removeAt(int *this, unsigned int index)
{
  unsigned int count = this[1]; // +0x04: number of stored elements
  unsigned int endIndex = count - 1;

  // Shift elements left if index is within valid range (excluding last element)
  if (index < endIndex) {
    int elementOffset = index * 12; // each element is 12 bytes
    do {
      // Copy entire element (two parts: 8 bytes then 4 bytes)
      unsigned long long *dest = (unsigned long long *)((int)this[0] + elementOffset);
      unsigned long long *src  = (unsigned long long *)((int)this[0] + 12 + elementOffset);
      *dest = *src;
      *(unsigned int *)(dest + 1) = *(unsigned int *)((int)src + 8);

      index++;
      elementOffset += 12;
    } while (index < endIndex);
  }

  // Decrement count
  this[1] = count - 1;
}