// FUNC_NAME: SomeClass::appendDataToBuffer
void SomeClass::appendDataToBuffer(void)
{
  undefined4 *newBlock;
  undefined4 *thisPtr; // unaff_ESI
  int dataSize; // unaff_EDI
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (dataSize != 0) {
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    // Allocate a new block of memory (0x10 bytes) via a virtual function call
    newBlock = (undefined4 *)(*(code *)**(undefined4 **)*thisPtr)(0x10, &local_c);
    *newBlock = local_4;          // +0x00: some value (likely flags or size)
    newBlock[1] = dataSize;       // +0x04: data size
    *(undefined1 *)(newBlock + 2) = 0; // +0x08: byte field (maybe type or padding)
    newBlock[3] = thisPtr[5];     // +0x0C: link to next block (or previous tail)
    thisPtr[3] = thisPtr[3] + dataSize; // +0x0C: total size accumulator
    thisPtr[5] = newBlock;        // +0x14: update tail pointer to new block
    *(undefined1 *)(thisPtr + 4) = 1; // +0x10: flag indicating buffer is non-empty
  }
  return;
}