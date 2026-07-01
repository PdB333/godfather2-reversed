// FUNC_NAME: FixedSizeAllocator::allocate
int __fastcall FixedSizeAllocator::allocate(int *this)
{
  undefined4 *newBlock;
  int currentCount;
  
  currentCount = this[2]; // +0x08: capacity (max number of elements)
  if (this[1] == currentCount) { // +0x04: current count == capacity?
    if (currentCount == 0) {
      currentCount = 1;
    }
    else {
      currentCount = currentCount * 2;
    }
    FixedSizeAllocator::grow(currentCount); // FUN_00984340 - grow the pool
  }
  newBlock = (undefined4 *)(*this + this[1] * 0x28); // +0x00: base pointer, +0x04: current count, each element is 0x28 bytes
  if (newBlock != (undefined4 *)0x0) {
    *newBlock = 0;
    FUN_004d3b00(0); // likely memset or constructor call
    newBlock[5] = 0; // +0x14
    newBlock[6] = 0; // +0x18
    newBlock[7] = 0; // +0x1C
    *(undefined1 *)(newBlock + 8) = 0; // +0x20 (byte)
    *(undefined1 *)((int)newBlock + 0x21) = 0; // +0x21 (byte)
    newBlock[9] = 0xffffffff; // +0x24: set to -1 (likely invalid index)
  }
  int oldCount = this[1]; // +0x04
  this[1] = oldCount + 1; // increment count
  return *this + oldCount * 0x28; // +0x00: base pointer, return pointer to allocated element
}