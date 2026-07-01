// FUNC_NAME: Container::pushBack
void __thiscall Container::pushBack(int *this, uint *value)
{
  int capacity = this[2];
  int size = this[1];
  
  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = size * 2;  // double the capacity
    }
    // Reallocate internal buffer to new capacity
    FUN_0082d130(capacity);
  }
  
  uint *slot = (uint *)(this[0] + this[1] * 4);
  this[1] = this[1] + 1;
  if (slot != (uint *)0x0) {
    *slot = *value;
  }
  return;
}