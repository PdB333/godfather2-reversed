// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined8 *element)
{
  undefined8 *dest;
  int capacity;
  
  capacity = this[2]; // +0x08 capacity
  if (this[1] == capacity) { // +0x04 size == capacity
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_0092dbc0(capacity); // reallocate array
  }
  dest = (undefined8 *)(*this + this[1] * 0xc); // +0x00 data pointer, element size 12 bytes
  this[1] = this[1] + 1; // increment size
  if (dest != (undefined8 *)0x0) {
    *dest = *element; // copy first 8 bytes
    *(undefined4 *)(dest + 1) = *(undefined4 *)(element + 1); // copy remaining 4 bytes
  }
  return;
}