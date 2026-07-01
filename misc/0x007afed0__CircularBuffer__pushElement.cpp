// FUNC_NAME: CircularBuffer::pushElement
void __thiscall CircularBuffer::pushElement(int *this, undefined4 *value)
{
  int writeIndex;
  
  // Compute write index as (head + count) mod capacity
  writeIndex = this[2] + this[3];  // head + count
  this[3] = this[3] + 1;           // increment count
  if (this[1] <= writeIndex) {     // if writeIndex >= capacity, wrap around
    writeIndex = writeIndex - this[1];
  }
  // Copy the value into the buffer at the computed index
  *(undefined4 *)(*this + writeIndex * 4) = *value;
  return;
}