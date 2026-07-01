// FUNC_NAME: Container::removeAt
void __thiscall Container::removeAt(int this, uint index)
{
  undefined4 *element;
  
  // Check if index is within valid range
  if (index < *(uint *)(this + 0x500)) {
    // If not removing the last element, shift elements down
    if (index < *(uint *)(this + 0x500) - 1) {
      // Calculate address of element at index (each element is 0x14 bytes)
      element = (undefined4 *)(this + 0x20 + index * 0x14);
      do {
        // Copy element data: shift element (i+1) to position i
        element[-8] = element[-3]; // Copy fields -3 to -8 to positions -8 to -4 (5 ints being moved)
        element[-7] = element[-2];
        element[-6] = element[-1];
        element[-5] = *element;
        element[-4] = element[1];
        index = index + 1;
        element = element + 5;
      } while (index < *(int *)(this + 0x500) - 1U);
    }
    // Decrease element count
    *(int *)(this + 0x500) = *(int *)(this + 0x500) + -1;
    // Clear the now-unused last slot (0x14 bytes = 5 uint32s)
    element = (undefined4 *)(this + *(int *)(this + 0x500) * 0x14);
    if (element != (undefined4 *)0x0) {
      *element = 0;
      element[4] = 0;
      element[3] = 0;
      element[2] = 0;
      element[1] = 0;
    }
  }
  return;
}