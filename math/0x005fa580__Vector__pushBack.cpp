// FUNC_NAME: Vector::pushBack
void Vector::pushBack(undefined4 *value)
{
  int *this = in_EAX;
  int capacity = this[2];
  int size = this[1];
  
  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_005fa940(capacity); // reallocate internal buffer
  }
  
  undefined4 *slot = (undefined4 *)(*this + size * 4);
  this[1] = size + 1;
  if (slot != (undefined4 *)0x0) {
    *slot = *value;
  }
}