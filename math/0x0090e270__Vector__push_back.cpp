// FUNC_NAME: Vector::push_back
void __thiscall Vector::push_back(int *this, undefined4 *value)
{
  undefined4 *elementPtr;
  int capacity;
  
  capacity = this[2];
  if (this[1] == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_0090dcd0(capacity); // reallocate/grow internal buffer
  }
  elementPtr = (undefined4 *)(*this + this[1] * 4); // pointer to end of array
  this[1] = this[1] + 1; // increment size
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = *value; // copy value into array
  }
  return;
}