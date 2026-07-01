// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, int *value)
{
  int capacity = this[2]; // +0x08: array capacity
  int size = this[1];      // +0x04: current element count

  if (size == capacity) {
    // Need to grow the array
    int newCapacity;
    if (capacity == 0) {
      newCapacity = 1;
    } else {
      newCapacity = capacity * 2;
    }
    // Grow/reallocate (FUN_00917a50 likely takes new capacity in elements)
    FUN_00917a50(newCapacity); // TODO: rename this grow function
  }

  // Insert new element at the end
  int *dataPtr = (int *)(this[0]); // +0x00: pointer to allocated buffer
  dataPtr[this[1]] = *value;       // Append value
  this[1]++;                        // Increment size
}