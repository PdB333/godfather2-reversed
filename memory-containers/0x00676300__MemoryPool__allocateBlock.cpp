// FUNC_NAME: MemoryPool::allocateBlock
void MemoryPool::allocateBlock(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  int this; // unaff_ESI
  int local_c;
  
  // +0x21f8: blockSize (size of each block in the pool)
  if (*(int *)(this + 0x21f8) != 0) {
    // +0x44: some offset, +0x40: another offset, +0x38: another, +0x3c: another
    iVar1 = *(int *)(this + 0x44);
    iVar2 = *(int *)(this + 0x40);
    // +0x21fc: currentBlockIndex (number of blocks allocated so far)
    *(int *)(this + 0x21fc) = *(int *)(this + 0x21fc) + 1;
    iVar3 = *(int *)(this + 0x38);
    iVar4 = *(int *)(this + 0x3c);
    iVar7 = *(int *)(this + 0x21f8);
    if (iVar7 <= *(int *)(this + 0x21fc)) {
      // Need to grow the pool: double the block count
      *(int *)(this + 0x21f8) = *(int *)(this + 0x21fc) * 2;
      // +0x21f4: pointer to block array (or inline storage if == this+0x2174)
      if (*(int *)(this + 0x21f4) == this + 0x2174) {
        // Currently using inline storage, allocate new block array
        uVar5 = FUN_00673070(); // allocate memory
        *(undefined4 *)(this + 0x21f4) = uVar5;
        local_c = 8;
        puVar6 = (undefined4 *)(this + 0x2178);
        do {
          // Copy 8 entries (32 bytes) from inline storage to new array
          *(undefined4 *)((int)puVar6 + *(int *)(this + 0x21f4) + -this + -0x2178) =
               puVar6[-1];
          *(undefined4 *)((int)puVar6 + *(int *)(this + 0x21f4) + -this + -0x2174) =
               *puVar6;
          *(undefined4 *)((int)puVar6 + *(int *)(this + 0x21f4) + (-0x2170 - this)) =
               puVar6[1];
          local_c = local_c + -1;
          *(undefined4 *)((int)puVar6 + *(int *)(this + 0x21f4) + (-0x216c - this)) =
               puVar6[2];
          puVar6 = puVar6 + 4;
        } while (local_c != 0);
      }
      else {
        // Already using heap-allocated array, reallocate with new size
        uVar5 = FUN_006730f0(*(int *)(this + 0x21f4), iVar7 * 4);
        *(undefined4 *)(this + 0x21f4) = uVar5;
      }
    }
    // Allocate a new block from the pool
    iVar7 = FUN_00673070();
    *(int *)(*(int *)(this + 0x21f4) + *(int *)(this + 0x21fc) * 4) = iVar7;
    // +0x16c: start of free list? +0x170: end of free list?
    *(int *)(this + 0x16c) = iVar7;
    *(int *)(this + 0x170) = iVar7 + ((((iVar1 - iVar2) - iVar3) + iVar4 >> 6) + 0x100) * 8;
    return;
  }
  // First-time initialization
  // +0x21f4: pointer to block array (initially points to inline storage at +0x2174)
  *(int **)(this + 0x21f4) = (int *)(this + 0x2174);
  // +0x21f8: blockSize = 0x20 (32 blocks initially)
  *(undefined4 *)(this + 0x21f8) = 0x20;
  // +0x21fc: currentBlockIndex = 0
  *(undefined4 *)(this + 0x21fc) = 0;
  // +0x2174: first block pointer (points to +0x174, the start of block data)
  *(int *)(this + 0x2174) = this + 0x174;
  // +0x16c: start of free list = +0x174
  *(int *)(this + 0x16c) = this + 0x174;
  // +0x170: end of free list = +0x2174
  *(int *)(this + 0x170) = this + 0x2174;
  return;
}