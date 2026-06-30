// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int *this, undefined4 *value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2]; // +0x08 capacity
  if (this[1] == capacity) { // +0x04 size == capacity
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_006bca00(capacity); // reallocate internal buffer
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00 buffer, +0x04 size
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into slot
  }
  return;
}