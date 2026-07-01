// FUNC_NAME: VectorPool::popBack
int __thiscall VectorPool::popBack(int *this, undefined4 *outElement)
{
  int elementSize;
  undefined4 *srcPtr;
  int result;
  
  elementSize = this[1] * 3; // element count * 3 (size of each element in 4-byte units)
  // Calculate pointer to last element: base + (count-1)*elementSize
  srcPtr = (undefined4 *)(*this + -0xc + this[1] * 0xc);
  
  if (outElement < srcPtr) {
    // Copy elements to fill the gap when removing from middle
    result = (int)srcPtr + (-1 - (int)outElement);
    elementSize = result * -0x55555555; // Divide by 3 (magic number for signed division)
    srcPtr = outElement + 3;
    // Copy 12 bytes (3 ints) at a time
    for (result = (result / 0xc + 1) * 0xc >> 2; result != 0; result = result - 1) {
      *outElement = *srcPtr;
      srcPtr = srcPtr + 1;
      outElement = outElement + 1;
    }
  }
  
  this[1] = this[1] + -1; // Decrement element count
  return elementSize;
}