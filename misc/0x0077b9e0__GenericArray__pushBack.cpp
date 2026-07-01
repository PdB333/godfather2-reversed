// FUNC_NAME: GenericArray::pushBack
void __thiscall GenericArray::pushBack(int *this, undefined4 *element)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2]; // +0x8: capacity
  if (this[1] == capacity) { // +0x4: size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_0077b550(capacity); // reallocate/resize internal buffer
  }
  slot = (undefined4 *)(*this + this[1] * 8); // +0x0: data pointer, each element is 8 bytes
  this[1] = this[1] + 1; // increment size
  if (slot != (undefined4 *)0x0) {
    *slot = *element; // copy first 4 bytes
    slot[1] = element[1]; // copy second 4 bytes
  }
  return;
}