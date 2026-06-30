// FUNC_NAME: MemoryPool::freeBlock
void __fastcall MemoryPool::freeBlock(undefined4 param_1, int *param_2)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  int unaff_FS_OFFSET;
  
  if (*param_2 != 0) {
    iVar3 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + *param_2;
    if ((*(int *)(iVar3 + 0x14) != 0) && (iVar1 = *(int *)(iVar3 + 0x14), iVar1 != 0)) {
      piVar2 = (int *)(DAT_01206880 + 0x14);
      *(undefined ***)*piVar2 = &PTR_LAB_01123be8;
      *piVar2 = *piVar2 + 4;
      *(int *)*piVar2 = iVar1;
      *piVar2 = *piVar2 + 4;
      *(undefined4 *)(iVar3 + 0x14) = 0;
      *(undefined4 *)(iVar3 + 0x18) = 0;
    }
    iVar3 = *param_2;
    piVar2 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8;
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar3;
    *piVar2 = *piVar2 + 4;
    *param_2 = 0;
    param_2[1] = 0;
  }
  return;
}