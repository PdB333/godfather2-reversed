// FUNC_NAME: GrowableArray::addElement
int __fastcall GrowableArray::addElement(int *this)
{
  int capacity = this[2]; // +0x08 capacity
  int size = this[1];     // +0x04 current size
  
  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity = capacity * 2;
    }
    GrowableArray::reserve(capacity); // FUN_0084c3f0 - grow the array
  }
  
  // Get pointer to new element slot (each element is 0xC bytes)
  int *newElement = (int *)(this[0] + size * 0xC); // +0x00 data pointer
  if (newElement != (int *)0x0) {
    newElement[0] = 0; // +0x00 first field
    newElement[1] = 0; // +0x04 second field
  }
  
  int oldSize = this[1]; // +0x04
  this[1] = oldSize + 1; // increment size
  return this[0] + oldSize * 0xC; // return pointer to the added element
}