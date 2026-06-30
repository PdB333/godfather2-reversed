// FUNC_NAME: Vector::push_back
void __thiscall Vector::push_back(int *this, undefined4 *value)
{
  undefined4 *slot;
  int newCapacity;
  
  newCapacity = this[2]; // +0x08 capacity
  if (this[1] == newCapacity) { // +0x04 size
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    FUN_006aa370(newCapacity); // Vector::reserve
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00 data pointer, +0x04 size
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into slot
  }
  return;
}