// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int *this, undefined4 *value)
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
    FUN_0097be60(capacity); // likely Vector::reserve or realloc
  }
  slot = (undefined4 *)(*this + this[1] * 4); // pointer to end slot
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *value; // copy value into slot
  }
  return;
}