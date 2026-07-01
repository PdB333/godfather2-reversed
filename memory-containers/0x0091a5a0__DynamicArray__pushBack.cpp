// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
{
  undefined4 *newBuffer;
  int newCapacity;
  
  newCapacity = this[2]; // +0x08 capacity
  if (this[1] == newCapacity) { // +0x04 size == capacity
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    FUN_009179f0(newCapacity); // likely reallocate/resize
  }
  newBuffer = (undefined4 *)(*this + this[1] * 4); // +0x00 buffer pointer, +0x04 size
  this[1] = this[1] + 1; // increment size
  if (newBuffer != (undefined4 *)0x0) {
    *newBuffer = *value; // copy value into new slot
  }
  return;
}