// FUNC_NAME: Vector::push_back
void __thiscall Vector::push_back(int *this, undefined4 *value)
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
    FUN_0082a890(newCapacity); // reallocate internal buffer
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00 buffer base + size*4
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into slot
  }
  return;
}