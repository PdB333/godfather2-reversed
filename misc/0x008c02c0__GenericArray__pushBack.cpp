// FUNC_NAME: GenericArray::pushBack
void __thiscall GenericArray::pushBack(int *this, undefined4 *element)
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
    FUN_008bddc0(capacity); // likely reallocate/resize
  }
  slot = (undefined4 *)(*this + this[1] * 8);
  this[1] = this[1] + 1;
  if (slot != (undefined4 *)0x0) {
    *slot = *element;
    slot[1] = element[1];
  }
  return;
}