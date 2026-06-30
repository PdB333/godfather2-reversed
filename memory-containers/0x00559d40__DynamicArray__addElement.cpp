// FUNC_NAME: DynamicArray::addElement
int* DynamicArray::addElement(void)
{
  int* thisPtr = reinterpret_cast<int*>(this); // this is in ESI, stored as int*
  int capacity = thisPtr[2]; // +0x08 - capacity
  int size = thisPtr[1]; // +0x04 - current element count

  if (size == capacity) {
    int newCapacity;
    if (capacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = capacity * 2;
    }
    // Grow the internal array (calls realloc-style function)
    growArray(newCapacity); // FUN_0055a0c0
  }

  // Calculate pointer to the new element (element size = 0x70 = 112 bytes)
  int* newElement = reinterpret_cast<int*>(thisPtr[0] + size * 0x70);

  if (newElement != nullptr) {
    // Zero out known fields in the new element
    // Offsets relative to element base (0x70 bytes total)
    newElement[0x48/4] = 0; // +0x48
    newElement[0x4c/4] = 0; // +0x4c
    newElement[0x50/4] = 0; // +0x50
    newElement[0x54/4] = 0; // +0x54
    newElement[0x58/4] = 0; // +0x58
    newElement[0x5c/4] = 0; // +0x5c
    newElement[0x40/4] = 0; // +0x40
    newElement[0x44/4] = 0; // +0x44
    newElement[0x60/4] = 0; // +0x60
    newElement[0x64/4] = 0; // +0x64
    newElement[0x68/4] = 0; // +0x68
  }

  // Increment size and return pointer to the newly added element
  thisPtr[1] = size + 1; // +0x04 (size)
  return reinterpret_cast<int*>(thisPtr[0] + size * 0x70);
}