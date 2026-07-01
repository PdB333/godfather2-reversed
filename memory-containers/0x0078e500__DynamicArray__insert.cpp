// FUNC_NAME: DynamicArray::insert
undefined4 * __thiscall DynamicArray::insert(int *this, uint index)
{
  undefined4 *elementPtr;
  uint currentSize;
  int capacity;
  
  capacity = this[2]; // +0x8: capacity
  if (this[1] == capacity) { // +0x4: size == capacity
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    DynamicArray::reserve(capacity); // FUN_0078e230
  }
  currentSize = this[1]; // +0x4: size
  elementPtr = (undefined4 *)(*this + currentSize * 4); // +0x0: data pointer
  if (index == currentSize) {
    this[1] = currentSize + 1; // append at end
    return elementPtr;
  }
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = elementPtr[-1]; // shift last element right
  }
  currentSize = this[1];
  while (currentSize = currentSize - 1, index < currentSize) {
    *(undefined4 *)(*this + currentSize * 4) = *(undefined4 *)(*this + -4 + currentSize * 4);
  }
  this[1] = this[1] + 1; // increment size
  return (undefined4 *)(*this + index * 4); // return pointer to inserted slot
}