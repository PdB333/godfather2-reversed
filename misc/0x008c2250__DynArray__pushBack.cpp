// FUNC_NAME: DynArray::pushBack
void DynArray::pushBack(undefined4* value)
{
  // Check if we need to grow the array
  if (mSize == mCapacity) {
    if (mCapacity == 0) {
      mCapacity = 1;
    }
    else {
      mCapacity *= 2;
    }
    // Reallocate internal buffer to new capacity
    reallocate(mCapacity);
  }
  // Write value at the end of the array
  undefined4* slot = mData + mSize;
  mSize++;
  if (slot != nullptr) {
    *slot = *value;
  }
}