// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int *this, int *value)
{
  int capacity = this[2]; // +0x08: capacity
  int size = this[1];    // +0x04: current number of elements

  if (size == capacity)
  {
    if (capacity == 0)
    {
      capacity = 1;
    }
    else
    {
      capacity = capacity * 2;
    }
    // Reallocate/grow internal storage to new capacity
    FUN_008be050(capacity); // Note: likely this->grow(capacity) or similar
  }

  // Write value at end of array
  int *dst = (int *)(this[0] + size * 4); // +0x00: data pointer
  this[1] = size + 1; // increment count

  if (dst != (int *)0x0)
  {
    *dst = *value;
  }
}