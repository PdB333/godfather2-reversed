// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int *this, undefined4 *value)
{
  int *data; // eax? Actually this[0] is data pointer
  int size = this[1]; // +0x04
  int capacity = this[2]; // +0x08

  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity *= 2;
    }
    // Reallocate internal buffer to new capacity
    FUN_008dd700(capacity); // likely Vector::reserve or realloc
  }

  // Write value at current end
  int *dest = (int *)(this[0] + size * 4); // +0x00 is data pointer
  this[1] = size + 1; // increment size
  if (dest != nullptr) {
    *dest = *value;
  }
}