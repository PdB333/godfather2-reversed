// FUNC_NAME: Buffer::pushElement
void __thiscall Buffer::pushElement(int *this, undefined4 *element)
{
  // Check if buffer is full (count == capacity & 0x3fffffff)
  if (this[1] == (this[2] & 0x3fffffff)) {
    // Resize buffer to accommodate more elements (grow by 4?)
    resizeBuffer(this, 4);
  }
  // Write element at buffer[count]
  *(undefined4 *)(*this + this[1] * 4) = *element;
  // Increment count
  this[1] = this[1] + 1;
}