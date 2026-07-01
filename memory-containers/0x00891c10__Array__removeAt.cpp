// FUNC_NAME: Array::removeAt
void __thiscall Array::removeAt(int *this, uint index)
{
  // Shift elements left to fill the removed slot
  if (index < this[1] - 1U) {
    do {
      *(undefined4 *)(*this + index * 4) = *(undefined4 *)(*this + 4 + index * 4);
      index = index + 1;
    } while (index < this[1] - 1U);
  }
  // Decrement array size
  this[1] = this[1] + -1;
  return;
}