// FUNC_NAME: Animated::updatePoseControl
void __thiscall Animated__updatePoseControl(int this, undefined4 *param_2)
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  float *pfVar4;
  undefined4 uVar5;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  undefined1 auStack_c [12];
  
  iVar2 = (**(code **)*param_2)();
  if (iVar2 == 0x27a0f69c) {
    uVar1 = *(uint *)(this + 0x128); // +0x128: bitfield flags
    if ((uVar1 >> 7 & 1) != 0) {
      // Bit 7: target facing direction
      FUN_00754d30(this + 0xb8, this + 0x80, 0, _DAT_00e52f84, 0, 1);
      return;
    }
    if ((uVar1 >> 4 & 1) != 0) {
      // Bit 4: look at target
      fStack_18 = DAT_00e44564 - *(float *)(this + 0xa0); // 0xa0: target position x
      fStack_14 = DAT_00e44564 - *(float *)(this + 0xa4); // 0xa4: target position y
      fStack_10 = DAT_00e44564 - *(float *)(this + 0xa8); // 0xa8: target position z
      FUN_00754d30(this + 0x94, &fStack_18, 1, _DAT_00e52f80, 0, 1);
      return;
    }
    uVar3 = _DAT_00e52f7c;
    if ((uVar1 >> 5 & 1) == 0) {
      // Bit 5 not set: check other bits
      if ((uVar1 >> 8 & 1) == 0) {
        // Bit 8 not set: default or bit 9
        if ((uVar1 >> 9 & 1) != 0) {
          // Bit 9: animation event
          FUN_007c8c30(auStack_c, &fStack_18);
          uVar3 = 2;
          if (*(int *)(this + 0x118) == 2) { // +0x118: animation state
            uVar3 = 6;
          }
          FUN_00754d30(auStack_c, &fStack_18, uVar3, _DAT_00e52f78, 0, 1);
          FUN_00754a60(DAT_00d6e928);
          return;
        }
        // Default case: bit 5,8,9 not set
        uVar5 = 0;
        pfVar4 = (float *)(this + 0x80); // +0x80: current position
        uVar3 = _DAT_00e52f84;
      }
      else {
        // Bit 8 set: look at direction
        fStack_18 = DAT_00e44564 - *(float *)(this + 0xa0);
        fStack_14 = DAT_00e44564 - *(float *)(this + 0xa4);
        fStack_10 = DAT_00e44564 - *(float *)(this + 0xa8);
        uVar5 = 3;
        if (*(int *)(this + 0x118) == 1) {
          uVar5 = 7;
        }
        pfVar4 = &fStack_18;
      }
    }
    else {
      // Bit 5 set: aim at target
      fStack_18 = DAT_00e44564 - *(float *)(this + 0xa0);
      fStack_14 = DAT_00e44564 - *(float *)(this + 0xa4);
      fStack_10 = DAT_00e44564 - *(float *)(this + 0xa8);
      uVar5 = 1;
      pfVar4 = &fStack_18;
    }
    FUN_00754d30(this + 0xac, pfVar4, uVar5, uVar3, 0, 1);
  }
  return;
}