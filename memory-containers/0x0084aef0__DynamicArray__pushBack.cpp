// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
{
  undefined4 *slot;
  int newCapacity;
  
  newCapacity = this[2]; // +0x08 capacity
  if (this[1] == newCapacity) { // +0x04 size == capacity
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    DynamicArray::reserve(newCapacity); // FUN_0084ac30
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00 data pointer, +0x04 size
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *param_2; // copy value into array
  }
  return;
}