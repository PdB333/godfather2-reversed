// FUNC_NAME: RingBuffer::popFront
void __thiscall RingBuffer::popFront(int *this, undefined4 *outData)
{
  undefined4 *src;
  
  src = (undefined4 *)(this[2] * 0x34 + *this);
  *outData = *src;
  FUN_004d3e20(src + 1); // likely memcpy or copy of some data block
  outData[5] = src[5];
  FUN_004d3e20(src + 6); // another copy
  outData[10] = src[10];
  outData[0xb] = src[0xb];
  outData[0xc] = src[0xc];
  this[2] = this[2] + 1; // advance read index
  this[3] = this[3] + -1; // decrement count
  if (this[1] <= this[2]) { // wrap around if at end
    this[2] = 0;
  }
  return;
}