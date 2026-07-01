// FUNC_NAME: GenericArray::reserve
void __thiscall GenericArray::reserve(int *this, uint newCapacity)
{
  undefined4 *newBuffer;
  uint i;
  undefined4 *destPtr;
  
  if ((uint)this[2] < newCapacity) {
    newBuffer = (undefined4 *)operatorNew(newCapacity * 4); // Allocate new array (4 bytes per element)
    if (*this != 0) { // If old buffer exists
      i = 0;
      destPtr = newBuffer;
      if (this[1] != 0) { // If count > 0
        do {
          if (destPtr != (undefined4 *)0x0) {
            *destPtr = *(undefined4 *)(*this + i * 4); // Copy element
          }
          i = i + 1;
          destPtr = destPtr + 1;
        } while (i < (uint)this[1]); // Copy all existing elements
      }
      operatorDelete(*this); // Free old buffer
    }
    *this = (int)newBuffer; // Set new buffer pointer
    this[2] = newCapacity; // Update capacity
  }
  return;
}