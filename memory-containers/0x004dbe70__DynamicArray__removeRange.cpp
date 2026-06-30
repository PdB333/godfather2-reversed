// FUNC_NAME: DynamicArray::removeRange
int * __thiscall DynamicArray::removeRange(int *this, int startIndex, int count)
{
  if (count != 0) {
    if ((uint)this[1] <= (uint)(startIndex + count)) {
      // Removing to end: just truncate
      this[1] = startIndex;
      *(undefined2 *)(*this + startIndex * 2) = 0;
      return this;
    }
    // Shift remaining elements left
    _memmove((void *)(*this + startIndex * 2),
             (void *)(*this + (startIndex + count) * 2),
             ((this[1] - startIndex) - count) * 2);
    this[1] = this[1] - count;
    // Null-terminate the new end
    *(undefined2 *)(*this + this[1] * 2) = 0;
  }
  return this;
}