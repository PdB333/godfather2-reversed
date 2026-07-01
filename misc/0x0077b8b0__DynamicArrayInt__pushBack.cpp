// FUNC_NAME: DynamicArrayInt::pushBack
void __thiscall DynamicArrayInt::pushBack(int *this, int *value)
{
  int *newBuffer;
  int capacity;
  
  capacity = this[2]; // +0x8: capacity
  if (this[1] == capacity) { // +0x4: size == capacity
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_0077b420(capacity); // reallocate buffer
  }
  newBuffer = (int *)(*this + this[1] * 4); // +0x0: buffer pointer, +0x4: size (element count)
  this[1] = this[1] + 1;
  if (newBuffer != (int *)0x0) {
    *newBuffer = *value;
  }
  return;
}