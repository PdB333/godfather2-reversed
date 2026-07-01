// FUNC_NAME: DynamicArray::pushBack

void __thiscall DynamicArray::pushBack(int *this, undefined4 *valuePtr)
{
  int *data;
  int size;
  int capacity;
  int newCapacity;
  undefined4 *slot;

  size = this[1]; // +0x04: current number of elements
  capacity = this[2]; // +0x08: allocated capacity

  if (size == capacity) {
    // Need to grow the array
    if (capacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = capacity * 2;
    }
    // Reallocate internal buffer to new capacity
    FUN_008e5f60(newCapacity); // likely DynamicArray::grow(newCapacity)
  }

  // Calculate pointer to the next slot
  slot = (undefined4 *)(this[0] + size * 4); // +0x00: pointer to data array
  this[1] = size + 1; // increment size

  if (slot != (undefined4 *)0x0) {
    *slot = *valuePtr; // copy the value
  }
  return;
}