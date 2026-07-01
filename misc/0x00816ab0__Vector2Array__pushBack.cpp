// FUNC_NAME: Vector2Array::pushBack
void __thiscall Vector2Array::pushBack(int *this, undefined8 *value)
{
  int capacity;
  undefined8 *dest;
  
  capacity = this[2]; // +0x08: capacity
  if (this[1] == capacity) { // +0x04: size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_00816760(capacity); // reallocate array
  }
  dest = (undefined8 *)(this[1] * 0x10 + *this); // +0x00: data pointer, each element is 0x10 bytes
  this[1] = this[1] + 1; // increment size
  if (dest != (undefined8 *)0x0) {
    *dest = *value;
    dest[1] = value[1]; // copy 16 bytes (two uint64)
  }
  return;
}