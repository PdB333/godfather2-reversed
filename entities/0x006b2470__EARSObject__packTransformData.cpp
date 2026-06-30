// FUNC_NAME: EARSObject::packTransformData
int EARSObject::packTransformData(int param_1, int *param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (param_2[1] != 0) {
    puVar3 = (undefined4 *)(param_1 + 0xc);
    do {
      iVar1 = *(int *)(*param_2 + uVar4 * 4);
      puVar3[-2] = *(undefined4 *)(iVar1 + 0x20);
      puVar3[-1] = *(undefined4 *)(iVar1 + 0x24);
      *puVar3 = *(undefined4 *)(iVar1 + 0x28);
      puVar3[1] = *(undefined4 *)(iVar1 + 0x2c);
      uVar2 = FUN_007914e0();
      puVar3[-3] = uVar2;
      uVar4 = uVar4 + 1;
      puVar3 = puVar3 + 5;
    } while (uVar4 < (uint)param_2[1]);
  }
  return param_2[1] * 0x14;
}