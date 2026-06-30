// FUNC_NAME: GenericCSA::setComponentData
int GenericCSA::setComponentData(int param_1, int *param_2, int param_3)
{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = param_2;
  (**(code **)(*param_2 + 8))(param_2);
  if (param_3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(param_3, piVar2);
  }
  FUN_005fc100(piVar2, uVar1);
  *(int **)(param_1 + 0x10) = param_2;  // +0x10 componentData pointer
  (**(code **)(*param_2 + 8))();
  if (param_3 != 0) {
    uVar1 = FUN_004265d0(param_3, *(undefined4 *)(param_1 + 0x10));
    *(undefined4 *)(param_1 + 0x14) = uVar1;  // +0x14 componentData2
    (**(code **)(*param_2 + 4))(param_3, 0);
    (**(code **)(*param_2 + 0xc))();
    return param_1;
  }
  *(undefined4 *)(param_1 + 0x14) = 0;  // +0x14 componentData2 = null
  (**(code **)(*param_2 + 0xc))();
  return param_1;
}