// FUNC_NAME: BinaryStream::writeFloat
undefined4 FUN_0062fe70(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  piVar1 = *(int **)(param_1 + 0xc);
  if (((*(int **)(param_1 + 8) <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 != 5)) {
    FUN_00627ac0(PTR_s_table_00e2a8b0);
  }
  iVar3 = FUN_00628820(1);
  puVar2 = *(undefined4 **)(param_1 + 8);
  *puVar2 = 3;
  puVar2[1] = (float)iVar3;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
  return 1;
}