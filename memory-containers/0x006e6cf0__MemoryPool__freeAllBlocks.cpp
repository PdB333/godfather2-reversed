// FUNC_NAME: MemoryPool::freeAllBlocks
void __thiscall MemoryPool::freeAllBlocks(int *this)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  
  // Iterate over all block arrays (likely pointer arrays)
  uVar5 = 0;
  if (this[1] != 0) { // +0x04: number of arrays
    do {
      iVar4 = *(int *)(*this + uVar5 * 4); // +0x00: pointer to array of block pointers
      if (iVar4 != 0) {
        // Walk the linked list of free blocks in this array and move them to the free list
        do {
          iVar1 = *(int *)(iVar4 + 4); // next block pointer (+0x04)
          *(int *)(iVar4 + 4) = this[2]; // +0x08: free list head
          this[3] = this[3] + -1; // +0x0C: count of blocks in use (decrement)
          this[2] = iVar4; // update free list head
          iVar4 = iVar1;
        } while (iVar1 != 0);
        *(undefined4 *)(*this + uVar5 * 4) = 0; // clear this array entry
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)this[1]);
  }
  // Free any remaining chained free lists (separate singly-linked list via +0x10)
  puVar3 = (undefined4 *)this[4]; // +0x10: chain of free blocks to delete
  while (puVar3 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*puVar3; // next pointer
    FUN_009c8eb0(puVar3); // likely operator delete or free
    puVar3 = puVar2;
  }
  this[4] = 0; // clear chain
  this[2] = 0; // free list head = 0
  return;
}