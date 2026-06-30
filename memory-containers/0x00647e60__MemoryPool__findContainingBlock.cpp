// FUNC_NAME: MemoryPool::findContainingBlock
uint __fastcall MemoryPool::findContainingBlock(int this, uint address)
{
  uint currentBlock;
  
  currentBlock = *(uint *)(this + 0x460); // +0x460: first block in pool list
  while( true ) {
    if (currentBlock == this + 0x448U) { // +0x448: end sentinel (null-like)
      return 0;
    }
    // Check if address falls within this block's range
    if ((currentBlock <= address) && (address < *(int *)(currentBlock + 4) + currentBlock)) break;
    currentBlock = *(uint *)(currentBlock + 0x18); // +0x18: next block pointer
  }
  return currentBlock;
}