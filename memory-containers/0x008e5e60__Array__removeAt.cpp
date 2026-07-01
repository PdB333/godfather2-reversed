// FUNC_NAME: Array::removeAt
void __thiscall Array::removeAt(int *this, uint index)
{
  undefined4 *src;
  int offset;
  
  if (index < this[1] - 1U) {
    offset = index << 4;
    do {
      src = (undefined4 *)(*this + offset);
      *src = *(undefined4 *)(*this + 0x10 + offset);
      src[1] = src[5];
      src[2] = src[6];
      src[3] = src[7];
      index = index + 1;
      offset = offset + 0x10;
    } while (index < this[1] - 1U);
  }
  this[1] = this[1] + -1;
  return;
}