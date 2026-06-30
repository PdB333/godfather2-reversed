// FUNC_NAME: MemoryPool::freeAll
void MemoryPool::freeAll(void)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int *this; // unaff_ESI

  uVar5 = 0;
  if (this[1] != 0) { // +0x04: numBuckets
    do {
      iVar4 = *(int *)(*this + uVar5 * 4); // +0x00: buckets array
      if (iVar4 != 0) {
        do {
          iVar1 = *(int *)(iVar4 + 0xc); // +0x0C: next free block pointer
          *(int *)(iVar4 + 0xc) = this[2]; // +0x08: freeList head
          this[3] = this[3] + -1; // +0x0C: numFreeBlocks
          this[2] = iVar4; // +0x08: freeList head = current block
          iVar4 = iVar1;
        } while (iVar1 != 0);
        *(undefined4 *)(*this + uVar5 * 4) = 0; // clear bucket entry
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)this[1]); // +0x04: numBuckets
  }
  puVar3 = (undefined4 *)this[4]; // +0x10: allocatedList head
  while (puVar3 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*puVar3; // +0x00: next allocated block
    FUN_009c8eb0(puVar3); // operator delete or memory deallocation
    puVar3 = puVar2;
  }
  this[4] = 0; // +0x10: allocatedList = NULL
  this[2] = 0; // +0x08: freeList = NULL
  return;
}