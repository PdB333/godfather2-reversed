// FUNC_NAME: DynamicArray::pushBack

void __thiscall DynamicArray::pushBack(int *this, int value)
{
  int oldSize;
  int *slotPtr;
  int newCapacity;

  // +0x00: buffer (int*), +0x04: size (int), +0x08: capacity (int)
  if (this[1] == this[2]) { // size == capacity
    if (this[2] == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = this[2] * 2;
    }
    // growArray allocates new buffer, updates this[0] and this[2]
    FUN_008b3980(newCapacity);
  }
  slotPtr = (int *)(this[0] + this[1] * 4); // buffer + size * sizeof(int)
  this[1] = this[1] + 1;                    // size++
  if (slotPtr != (int *)0x0) {
    *slotPtr = value;                       // buffer[oldSize] = value
  }
  return;
}