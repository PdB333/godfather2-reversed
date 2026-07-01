// FUNC_NAME: DynamicArray::insertAt
undefined4 * __thiscall DynamicArray::insertAt(int *this, uint index)
{
  undefined4 *elementPtr;
  uint currentSize;
  int capacity;
  
  capacity = this[2]; // +0x08: capacity
  if (this[1] == capacity) { // +0x04: current size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_00941b90(capacity); // reallocate/grow array
  }
  currentSize = this[1]; // +0x04: current size
  elementPtr = (undefined4 *)(*this + currentSize * 8); // +0x00: data pointer
  if (index == currentSize) {
    this[1] = currentSize + 1;
    return elementPtr;
  }
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = elementPtr[-2];
    elementPtr[1] = elementPtr[-1];
  }
  currentSize = this[1];
  while (currentSize = currentSize - 1, index < currentSize) {
    elementPtr = (undefined4 *)(*this + currentSize * 8);
    *elementPtr = *(undefined4 *)(*this + -8 + currentSize * 8);
    elementPtr[1] = elementPtr[-1];
  }
  this[1] = this[1] + 1;
  return (undefined4 *)(*this + index * 8);
}