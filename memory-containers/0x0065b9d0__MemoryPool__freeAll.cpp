// FUNC_NAME: MemoryPool::freeAll
void MemoryPool::freeAll(void)
{
  // in_EAX points to this (MemoryPool*)
  // this->firstFreeBlock is at offset 0x00
  // this->blockSize is at offset 0x04
  // this->blockCount is at offset 0x08
  // this->freeListHead is at offset 0x0C (global DAT_01223ba0)
  // this->totalFreeBlocks is at offset 0x10 (global _DAT_01223b98)
  // this->initializedFlag is at offset 0x14 (global _DAT_01223ba4)
  
  undefined4 *currentBlock;
  undefined4 *nextBlock;
  
  currentBlock = (undefined4 *)*in_EAX;  // Dereference this to get first block in pool
  
  while (nextBlock = currentBlock, nextBlock != (undefined4 *)0x0) {
    currentBlock = (undefined4 *)*nextBlock;  // Follow linked list
    
    // Check if block is full (blockSize == allocatedSize at offset 0x08)
    if (nextBlock[2] == *(int *)nextBlock[1]) {
      // Mark block as available (offset 0x05 in block header)
      *(undefined1 *)((int *)nextBlock[1] + 5) = 1;
    }
    
    // One-time initialization of global free list
    if ((_DAT_01223ba4 & 1) == 0) {
      _DAT_01223ba4 = _DAT_01223ba4 | 1;
      FUN_0065ba80();  // Initialize free list
      _atexit((_func_4879 *)&LAB_00d51450);  // Register cleanup
    }
    
    // Return block to global free list
    _DAT_01223b98 = _DAT_01223b98 + -1;  // Decrement total free blocks
    *nextBlock = DAT_01223ba0;  // Link to current free list head
    DAT_01223ba0 = nextBlock;   // Update free list head
  }
  return;
}