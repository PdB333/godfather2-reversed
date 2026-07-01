// FUNC_NAME: PlayerActionableTargetSM::updateTargeting
undefined1 __thiscall PlayerActionableTargetSM::updateTargeting(int this, int targetIndex, char param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  // +0x20: offset to target array, each entry 0x24 bytes
  iVar1 = *(int *)(this + targetIndex * 0x24 + 0x20);
  targetIndex._0_1_ = 0;
  if ((iVar1 == 0) || (iVar1 + -0x48 == 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_00791300();
    if (this == 0) {
      this = 0;
    }
    else {
      this = this + 0x10;
    }
    FUN_00791350(this);
    if ((*(byte *)(iVar1 + 0x17) & 1) != 0) {
      FUN_00791e00(0);
      if (iVar2 != 0) {
        iVar3 = FUN_0043b870(DAT_01131040);
        if (iVar3 != 0) {
          FUN_009b1970(1);
        }
      }
    }
    if (param_3 != '\0') {
      iVar3 = FUN_008c74d0(0x637b907);
      if (iVar3 != 0) {
        FUN_008c1190(iVar1 + -0x48);
        targetIndex._0_1_ = 1;
      }
    }
  }
  FUN_0090a9f0();
  if (iVar2 != 0) {
    FUN_00737940(3,0);
  }
  return (undefined1)targetIndex;
}