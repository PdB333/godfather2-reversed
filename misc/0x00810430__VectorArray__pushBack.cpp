// FUNC_NAME: VectorArray::pushBack
void __thiscall VectorArray::pushBack(int *this, undefined4 *value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2]; // +0x08: capacity
  if (this[1] == capacity) { // +0x04: size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_0080ff20(capacity); // reallocate/resize internal buffer
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00: data pointer, +0x04: size
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into new slot
  }
  return;
}