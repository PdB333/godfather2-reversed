// FUNC_NAME: GrowableArray::pushBack
void __fastcall GrowableArray::pushBack(int *thisArray)
{
  int capacity = thisArray[2]; // +0x08: capacity
  if (thisArray[1] == capacity) { // +0x04: current size
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    GrowableArray::reserve(capacity);
  }
  int newSize = thisArray[1]; // +0x04: current size
  thisArray[1] = newSize + 1;
  // +0x00: data pointer, each element is 0x130 bytes
  if (*(thisArray[0] + newSize * 0x130) != 0) {
    GrowableArray::destroyElement();
    return;
  }
  return;
}