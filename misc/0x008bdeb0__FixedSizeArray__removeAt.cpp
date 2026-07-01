// FUNC_NAME: FixedSizeArray::removeAt
void __thiscall FixedSizeArray::removeAt(int *this, uint index)
{
  // Remove element at index by shifting subsequent elements left.
  // this[0] = pointer to array data
  // this[1] = current element count
  if (index < this[1] - 1U) {
    do {
      *(undefined4 *)(*this + index * 4) = *(undefined4 *)(*this + 4 + index * 4);
      index = index + 1;
    } while (index < this[1] - 1U);
  }
  // Decrement count
  this[1] = this[1] + -1;
  return;
}