// FUNC_NAME: FixedSizeQueue::removeAtIndex
void __thiscall FixedSizeQueue::removeAtIndex(int *this, uint index)
{
  // this[0] = pointer to array of elements (each 8 bytes)
  // this[1] = current count of elements
  undefined4 *currentElement;
  
  // Only shift if index is not the last element
  if (index < (uint)(this[1] - 1)) {
    do {
      // Overwrite element at index with element at index+1
      currentElement = (undefined4 *)(*this + index * 8);
      *currentElement = *(undefined4 *)(*this + 8 + index * 8);
      currentElement[1] = *(undefined4 *)(*this + 12 + index * 8); // currentElement[3] offset
      index = index + 1;
    } while (index < (uint)(this[1] - 1));
  }
  // Decrement count
  this[1] = this[1] - 1;
  return;
}