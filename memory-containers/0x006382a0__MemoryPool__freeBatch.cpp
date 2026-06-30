// FUNC_NAME: MemoryPool::freeBatch
void __fastcall MemoryPool::freeBatch(void *this)
{
  undefined4 *currentBlock;
  undefined4 *nextBlock;
  undefined4 *blockToFree;
  
  currentBlock = *(undefined4 **)((int)this + 0x48);
  while (currentBlock != (undefined4 *)0x0 && (nextBlock = (undefined4 *)currentBlock[2], blockToFree <= nextBlock)) {
    currentBlock[3] = *nextBlock;
    currentBlock[4] = nextBlock[1];
    currentBlock[2] = currentBlock + 3;
    *(undefined4 *)((int)this + 0x48) = *currentBlock;
    *currentBlock = *(undefined4 *)(*(int *)((int)this + 0x10) + 0xc);
    *(undefined4 **)(*(int *)((int)this + 0x10) + 0xc) = currentBlock;
    *(undefined1 *)((int)currentBlock + 5) = 0;
    *(undefined1 *)(currentBlock + 1) = 10;
    currentBlock = *(undefined4 **)((int)this + 0x48);
  }
  return;
}