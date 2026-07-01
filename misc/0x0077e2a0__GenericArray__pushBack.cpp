// FUNC_NAME: GenericArray::pushBack
void __thiscall GenericArray::pushBack(int *this, undefined4 *value)
{
  undefined4 *elementPtr;
  int currentSize;
  
  currentSize = this[2]; // +0x08 capacity
  if (this[1] == currentSize) { // +0x04 size == capacity
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2;
    }
    FUN_0077d9b0(currentSize); // reallocate array
  }
  elementPtr = (undefined4 *)(*this + this[1] * 8); // +0x00 data pointer, +0x04 size
  this[1] = this[1] + 1; // increment size
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = *value; // copy first 4 bytes
    elementPtr[1] = value[1]; // copy next 4 bytes (8-byte element)
  }
  return;
}