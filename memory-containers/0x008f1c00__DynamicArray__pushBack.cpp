// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
{
  undefined4 *ptr;
  int capacity;
  
  capacity = this[2]; // +0x8: capacity (max size)
  if (this[1] == capacity) { // +0x4: current size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    // Grow the array to new capacity (FUN_008f1820 likely reallocate/grow)
    FUN_008f1820(capacity);
  }
  ptr = (undefined4 *)(*this + this[1] * 4); // +0x0: data pointer, index = size
  this[1] = this[1] + 1; // increment size
  if (ptr != (undefined4 *)0x0) {
    *ptr = *value; // copy value to new slot
  }
  return;
}