// FUNC_NAME: Array::pushBack

void __thiscall Array::pushBack(undefined4 value)
{
  // this points to mData (int**), mSize (int), mCapacity (int) at +0x00, +0x04, +0x08
  int currentSize = this->mSize;
  if (currentSize == this->mCapacity) {
    int newCapacity;
    if (currentSize == 0) {
      newCapacity = 1;
    } else {
      newCapacity = currentSize * 2;
    }
    // grow the internal buffer to newCapacity
    this->grow(newCapacity);
  }
  // store value at end of array
  this->mData[currentSize] = value;
  this->mSize = currentSize + 1;
}