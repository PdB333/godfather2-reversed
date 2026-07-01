// FUNC_NAME: DynamicArray::insertAt
int __thiscall DynamicArray::insertAt(int *this, uint index)
{
  uint currentSize;
  int result;
  undefined4 *elementPtr;
  int newCapacity;
  
  newCapacity = this[2]; // +0x08 capacity
  if (this[1] == newCapacity) { // +0x04 size == capacity
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    FUN_007f2ad0(newCapacity); // reallocate
  }
  currentSize = this[1]; // +0x04 size
  if (index != currentSize) {
    // Shift elements after index forward by one slot (0x14 bytes each)
    elementPtr = (undefined4 *)(*this + currentSize * 0x14); // +0x00 data pointer
    if (elementPtr != (undefined4 *)0x0) {
      *elementPtr = elementPtr[-5];
      elementPtr[1] = elementPtr[-4];
      elementPtr[2] = elementPtr[-3];
      elementPtr[3] = elementPtr[-2];
      elementPtr[4] = elementPtr[-1];
    }
    currentSize = this[1] - 1; // +0x04 size
    if (index < currentSize) {
      newCapacity = currentSize * 0x14;
      result = currentSize - index;
      do {
        elementPtr = (undefined4 *)(*this + newCapacity);
        *elementPtr = *(undefined4 *)(*this + -0x14 + newCapacity);
        elementPtr[1] = elementPtr[-4];
        elementPtr[2] = elementPtr[-3];
        elementPtr[3] = elementPtr[-2];
        newCapacity = newCapacity + -0x14;
        result = result + -1;
        elementPtr[4] = elementPtr[-1];
      } while (result != 0);
    }
    this[1] = this[1] + 1; // +0x04 size++
    elementPtr = (undefined4 *)(*this + index * 0x14);
    if (elementPtr != (undefined4 *)0x0) {
      *elementPtr = 0xbadbadba; // sentinel value
      elementPtr[1] = 0xbeefbeef;
      elementPtr[2] = 0xeac15a55;
      elementPtr[3] = 0x91100911;
    }
    return *this + index * 0x14;
  }
  // Append at end
  elementPtr = (undefined4 *)(*this + currentSize * 0x14);
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = 0xbadbadba;
    elementPtr[1] = 0xbeefbeef;
    elementPtr[2] = 0xeac15a55;
    elementPtr[3] = 0x91100911;
  }
  result = this[1]; // +0x04 size
  this[1] = result + 1;
  return *this + result * 0x14;
}