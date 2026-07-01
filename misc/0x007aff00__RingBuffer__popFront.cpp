// FUNC_NAME: RingBuffer::popFront
void __thiscall RingBuffer::popFront(int *this, undefined4 *outValue)
{
  // Read the value at the current read index (this[2] is readIndex)
  *outValue = *(undefined4 *)(*this + this[2] * 4);
  
  // Advance read index (this[2] is readIndex)
  this[2] = this[2] + 1;
  
  // Decrement count (this[3] is count)
  this[3] = this[3] + -1;
  
  // Wrap read index if it reaches capacity (this[1] is capacity)
  if (this[1] <= this[2]) {
    this[2] = 0;
  }
  
  return;
}