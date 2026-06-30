// FUNC_NAME: Vector::pushBack
// Address: 0x005e6ce0
// Role: Appends an element (4 bytes) to a dynamic array, doubling capacity if needed.
// Class layout (assumed): +0x00 pointer to data, +0x04 size, +0x08 capacity

void __thiscall Vector::pushBack(int *this, int element)
{
  int *dataPtr = (int *)this[0];   // +0x00: data pointer
  int size = this[1];              // +0x04: current element count
  int capacity = this[2];          // +0x08: allocated capacity

  if (size == capacity)
  {
    int newCapacity;
    if (capacity == 0)
    {
      newCapacity = 1;
    }
    else
    {
      newCapacity = capacity * 2;  // double capacity
    }
    FUN_005e6ff0(newCapacity);     // reallocate data array
  }

  int *slot = dataPtr + size;      // slot at index = size
  this[1] = size + 1;             // increment size
  if (slot != (int *)0x0)          // safety check (should always be valid)
  {
    *slot = element;
  }
  return;
}