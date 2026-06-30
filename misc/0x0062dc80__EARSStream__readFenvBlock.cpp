// FUNC_NAME: EARSStream::readFenvBlock
bool EARSStream::readFenvBlock(int streamContext)
{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 *puVar6;
  
  puVar1 = *(undefined4 **)(streamContext + 8);
  if ((puVar1[-2] == 6) && (*(char *)(puVar1[-1] + 6) == '\0')) {
    puVar6 = (undefined4 *)(puVar1[-1] + 0x10);
  }
  else {
    puVar6 = (undefined4 *)(streamContext + 0x40);
  }
  *puVar1 = *puVar6;
  puVar1[1] = puVar6[1];
  *(int *)(streamContext + 8) = *(int *)(streamContext + 8) + 8;
  if (*(uint *)(*(int *)(streamContext + 0x10) + 0x20) <= *(uint *)(*(int *)(streamContext + 0x10) + 0x24)) {
    FUN_00627360();
  }
  puVar1 = *(undefined4 **)(streamContext + 8);
  *puVar1 = 4;
  uVar4 = FUN_00638920(streamContext,"__fenv",6);
  puVar1[1] = uVar4;
  *(int *)(streamContext + 8) = *(int *)(streamContext + 8) + 8;
  iVar2 = *(int *)(streamContext + 8);
  iVar3 = *(int *)(iVar2 + -8);
  if (iVar3 == 3) {
    if ((float)(int)*(float *)(iVar2 + -4) == *(float *)(iVar2 + -4)) {
      piVar5 = (int *)FUN_00637f10();
      goto LAB_0062dd28;
    }
  }
  else if (iVar3 == 4) {
    piVar5 = (int *)FUN_00637f90();
    goto LAB_0062dd28;
  }
  piVar5 = (int *)FUN_00637ea0();
LAB_0062dd28:
  *(int *)(iVar2 + -8) = *piVar5;
  *(int *)(iVar2 + -4) = piVar5[1];
  piVar5 = (int *)(*(int *)(streamContext + 8) + -8);
  if (piVar5 == (int *)0x0) {
    return true;
  }
  return *piVar5 != 0;
}