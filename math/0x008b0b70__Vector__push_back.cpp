// FUNC_NAME: Vector::push_back
void __thiscall Vector::push_back(int *this, undefined4 *value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2]; // +0x8: capacity
  if (this[1] == capacity) { // +0x4: size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_008aff60(capacity); // reallocate/grow internal buffer
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x0: data pointer
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into slot
  }
  return;
}