// FUNC_NAME: PairArray::pushBack

void __thiscall PairArray::pushBack(int *this, undefined4 *pairData)
{
  undefined4 *newBuffer;
  int capacity;
  
  capacity = this[2]; // +0x08: capacity
  if (this[1] == capacity) { // +0x04: size
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity = capacity * 2;
    }
    FUN_0077b550(capacity); // Realloc buffer for new capacity
  }
  newBuffer = (undefined4 *)(this[0] + this[1] * 8); // +0x00: buffer pointer, +0x04: size
  this[1] = this[1] + 1; // Increment size
  if (newBuffer != (undefined4 *)0x0) {
    *newBuffer = *pairData; // Copy first dword
    newBuffer[1] = pairData[1]; // Copy second dword
  }
  return;
}