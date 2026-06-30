// FUNC_NAME: GrowableArray::resizeCapacity
void __thiscall GrowableArray::resizeCapacity(int *this, uint newCapacity)
{
  undefined4 *newBuffer;
  uint i;
  undefined4 *destPtr;
  
  // Only grow if we need more capacity
  if ((uint)this[2] < newCapacity) {
    // Allocate new buffer (uses internal allocator)
    newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4);
    
    // If we have existing data, copy it
    if (*this != 0) {
      i = 0;
      destPtr = newBuffer;
      if (this[1] != 0) {
        do {
          // Copy each element (if destination buffer is valid)
          if (destPtr != (undefined4 *)0x0) {
            *destPtr = *(undefined4 *)(*this + i * 4);
          }
          i = i + 1;
          destPtr = destPtr + 1;
        } while (i < (uint)this[1]);  // Copy up to current size
      }
      // Free old buffer
      FUN_009c8f10(*this);
    }
    // Update buffer pointer and new capacity
    *this = (int)newBuffer;
    this[2] = newCapacity;  // +0x08: new capacity
  }
  return;
}