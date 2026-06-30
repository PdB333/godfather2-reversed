// FUNC_NAME: MemoryAllocator::allocateAlignedBlock
void MemoryAllocator::allocateAlignedBlock(int param_1, undefined4 *param_2)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  piVar1 = *(int **)(param_1 + 0x18); // +0x18: current allocation pointer
  iVar2 = *piVar1;                     // first field: element count
  *(int **)(param_1 + 0x18) = piVar1 + 1; // advance past count
  iVar3 = piVar1[1];                   // second field: alignment
  *(int **)(param_1 + 0x18) = piVar1 + 2; // advance past alignment
  uVar5 = (int)piVar1 + iVar3 + 7 & ~(iVar3 - 1U); // align base pointer
  uVar4 = iVar2 * 0x18 + uVar5 + 0xf & 0xfffffff0; // total size with 16-byte alignment
  *(uint *)(param_1 + 0x18) = uVar4 + 0x40; // update allocation pointer with header overhead
  (*(code *)*param_2)(CONCAT44(iVar2,-(uint)(iVar2 != 0) & uVar5),iVar3,uVar4); // call constructor callback
  return;
}