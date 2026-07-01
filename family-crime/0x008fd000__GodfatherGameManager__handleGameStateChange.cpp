// FUNC_NAME: GodfatherGameManager::handleGameStateChange
void __thiscall GodfatherGameManager::handleGameStateChange(int this, int param_2, uint param_3)
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_14 [16];
  undefined4 local_4;
  
  iVar1 = **(int **)(DAT_012233a0 + 4);
  if (iVar1 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = iVar1 + -0x1f30;
    if ((iVar3 != 0) && ((*(uint *)(iVar1 + 0x56c) >> 5 & 1) == 0)) {
      FUN_0040c1f0(0xff000000,0,0,1);
    }
  }
  param_3 = param_3 | 0x104;
  if (param_2 != 0) {
    FUN_007dd020(param_3);
    return;
  }
  if (iVar3 != 0) {
    iVar1 = FUN_00471610();
    iVar1 = FUN_00811840(iVar1 + 0x30,*(undefined4 *)(this + 0x18));
    if (iVar1 != 0) {
      local_4 = 0;
      FUN_00811b90(local_14);
      uVar2 = FUN_008111d0();
      FUN_0079e3c0(uVar2,param_3,0,local_14);
      return;
    }
    uVar2 = FUN_00471610();
    FUN_0079e3c0(uVar2,param_3,0,0);
  }
  return;
}