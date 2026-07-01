// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
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
    DynamicArray::resize(currentSize); // grow capacity
  }
  elementPtr = (undefined4 *)(*this + this[1] * 4); // +0x00 array pointer, +0x04 size
  this[1] = this[1] + 1;
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = *value;
  }
  return;
}