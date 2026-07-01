// FUNC_NAME: PlayerSM::updateStateMachine
void PlayerSM::updateStateMachine(undefined4 param_1, int *param_2)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined8 uStack_c;
  undefined4 uStack_4;
  
  param_2 = (int *)*param_2;
  if (((param_2[5] == 0) || (param_2[5] == 0x48)) || (cVar1 = FUN_00481660(), cVar1 == '\\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  cVar1 = FUN_0064bb50(uVar3);
  iVar2 = param_2[5];
  if (cVar1 == '\\0') {
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = iVar2 + -0x48;
    }
    FUN_004a8f30(iVar2);
    FUN_004a93a0(param_1,&local_20);
  }
  else {
    if ((iVar2 == 0) || (iVar2 == 0x48)) {
      iVar2 = 0;
    }
    else {
      iVar2 = iVar2 + 0x10;
    }
    FUN_004a8ec0(iVar2);
    FUN_004a9320(param_1,&local_20);
  }
  uVar3 = (**(code **)(*param_2 + 0x14))();
  FUN_0064bb50(uVar3);
  uVar3 = (**(code **)(*param_2 + 0x1c))();
  FUN_0064bb50(uVar3);
  iVar2 = (**(code **)(*param_2 + 0x28))();
  local_20 = *(undefined4 *)(iVar2 + 0x20);
  uStack_1c = *(undefined4 *)(iVar2 + 0x24);
  uStack_c = *(undefined8 *)(iVar2 + 0x20);
  uStack_18 = *(undefined4 *)(iVar2 + 0x28);
  uStack_4 = uStack_18;
  FUN_004a9b90(param_1,&uStack_c);
  return;
}