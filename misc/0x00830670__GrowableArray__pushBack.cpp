// FUNC_NAME: GrowableArray::pushBack
void __thiscall GrowableArray::pushBack(int *this, undefined4 *value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2]; // +0x08: capacity
  if (this[1] == capacity) { // +0x04: size == capacity
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    GrowableArray::reserve(capacity); // FUN_0082ab90 - reallocate/reserve
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00: data pointer, +0x04: size
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into new slot
  }
  return;
}