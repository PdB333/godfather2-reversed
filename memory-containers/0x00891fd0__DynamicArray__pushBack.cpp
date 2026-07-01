// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
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
    FUN_00891ce0(capacity); // reallocate/grow array
  }
  slot = (undefined4 *)(*this + this[1] * 4); // +0x00: data pointer
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy element
  }
  return;
}