// FUNC_NAME: RingBuffer::pushElement
void __thiscall RingBuffer::pushElement(uint *this, Element *element)
{
  // Decrement write index (offset +0x00)
  this[0] = this[0] - 1;
  // Wrap if underflow (unsigned wrap yields > 0x7fffffff)
  if (0x7fffffff < this[0]) {
    this[0] = this[3] - 1; // capacity at offset +0x0C
  }
  // Compute slot address: buffer (offset +0x08) + writeIndex * elementSize (0x1c)
  Element *slot = (Element *)(this[2] + this[0] * 0x1c);
  // Copy 28-byte element (3 qwords + 1 dword)
  *slot = *element;
  // If read index (offset +0x04) equals new write index, also decrement read index
  if (this[1] == this[0]) {
    this[1] = this[1] - 1;
    if (0x7fffffff < this[1]) {
      this[1] = this[3] - 1;
    }
  }
}