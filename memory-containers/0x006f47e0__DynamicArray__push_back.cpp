// FUNC_NAME: DynamicArray::push_back
void __thiscall DynamicArray::push_back(int *this, undefined4 *element)
{
  int capacity = this[2];             // +0x08: capacity
  int size = this[1];                 // +0x04: size

  if (size == capacity) {             // Need to grow?
    int newCapacity;
    if (capacity == 0) {
      newCapacity = 1;
    } else {
      newCapacity = capacity * 2;
    }
    DynamicArray::grow(newCapacity);  // Reallocate and update +0x00 and +0x08
  }

  undefined4 *slot = (undefined4 *)(this[0] + this[1] * 4);  // +0x00: data
  this[1] = this[1] + 1;             // Increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *element;
  }

  return;
}