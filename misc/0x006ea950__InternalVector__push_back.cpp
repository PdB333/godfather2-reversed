// FUNC_NAME: InternalVector::push_back
void __thiscall push_back(int *this, undefined4 *value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2];
  if (this[1] == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    // +0x00: data pointer, +0x04: size, +0x08: capacity
    reallocate(capacity); // FUN_006ea5e0 - resize internal buffer
  }
  slot = (undefined4 *)(*this + this[1] * 4); // calculate slot for new element
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into slot
  }
  return;
}