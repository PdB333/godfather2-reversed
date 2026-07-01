// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int *this, const int *element)
{
  int size = this[1];       // +0x04: current size
  int capacity = this[2];   // +0x08: allocated capacity

  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity *= 2;
    }
    // Reallocate internal buffer to new capacity
    FUN_0092db60(capacity); // likely Vector::reserve or reallocate
  }

  int *slot = (int *)(this[0] + size * 4); // +0x00: data pointer
  this[1] = size + 1; // increment size
  if (slot != nullptr) {
    *slot = *element; // copy element
  }
}