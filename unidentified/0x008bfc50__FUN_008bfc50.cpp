// FUNC_NAME: SomeClass::copyMatrixArray
int SomeClass::copyMatrixArray(int param_1, int *param_2)
{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (param_2[1] != 0) {
    puVar2 = (undefined4 *)(param_1 + 8);
    do {
      iVar1 = *(int *)(*param_2 + uVar3 * 4);
      puVar2[-2] = *(undefined4 *)(iVar1 + 0x20);
      puVar2[-1] = *(undefined4 *)(iVar1 + 0x24);
      *puVar2 = *(undefined4 *)(iVar1 + 0x28);
      puVar2[1] = *(undefined4 *)(iVar1 + 0x2c);
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 4;
    } while (uVar3 < (uint)param_2[1]);
  }
  return param_2[1] << 4;
}