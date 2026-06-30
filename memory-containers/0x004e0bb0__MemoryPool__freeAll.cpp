// FUNC_NAME: MemoryPool::freeAll
void MemoryPool::freeAll(void)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int *this; // unaff_ESI

  // Free all blocks in each free list (indexed by block size)
  uVar5 = 0;
  if (this[1] != 0) { // +0x04: numFreeLists
    do {
      iVar4 = *(int *)(*this + uVar5 * 4); // +0x00: freeLists array
      if (iVar4 != 0) {
        do {
          iVar1 = *(int *)(iVar4 + 4); // next block in list
          *(int *)(iVar4 + 4) = this[2]; // +0x08: freeListHead
          this[3] = this[3] + -1; // +0x0C: numFreeBlocks
          this[2] = iVar4; // prepend to free list
          iVar4 = iVar1;
        } while (iVar1 != 0);
        *(undefined4 *)(*this + uVar5 * 4) = 0; // clear the free list slot
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)this[1]);
  }

  // Free all blocks in the overflow list
  puVar3 = (undefined4 *)this[4]; // +0x10: overflowList
  while (puVar3 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*puVar3; // next overflow block
    FUN_009c8eb0(puVar3); // operator delete or memory deallocation
    puVar3 = puVar2;
  }

  this[4] = 0; // +0x10: overflowList = NULL
  this[2] = 0; // +0x08: freeListHead = NULL
  return;
}