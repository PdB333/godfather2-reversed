// FUNC_NAME: Player::updateHealthRegeneration
void __thiscall Player::updateHealthRegeneration(int *this, undefined4 param_2, int param_3, int param_4)
{
  int iVar1;
  float10 fVar2;
  float fStack_4c;
  undefined1 auStack_48 [4];
  int iStack_44;
  undefined4 uStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  undefined8 uStack_34;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  undefined4 uStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_10;
  uint uStack_c;
  undefined4 uStack_8;
  uint uStack_4;
  
  // Get current game time (vtable +0xC0 = getTime())
  fVar2 = (float10)(**(code **)(*this + 0xc0))();
  if ((float10)0 < fVar2) {
    fVar2 = (float10)(**(code **)(*this + 0xc0))();
    // Calculate health regeneration amount based on time and global multiplier
    fStack_4c = (float)(fVar2 * (float10)DAT_00d5ddec);
    if (fVar2 * (float10)DAT_00d5ddec < (float10)0) {
      fStack_4c = 0.0;
    }
    FUN_0084dd20(); // Some initialization function
    uStack_4 = uStack_4 | 0x48;
    uStack_c = (uint)this[0x1a3] >> 2; // +0x68C - some state/flag
    fStack_1c = fStack_4c;
    uStack_18 = param_2;
    uStack_8 = DAT_01205224; // Global pointer
    if (param_3 == 0) {
      iVar1 = FUN_00471610(); // Get player entity
      uStack_28 = *(undefined8 *)(iVar1 + 0x30); // +0x30 - position/transform
      uStack_20 = *(undefined4 *)(iVar1 + 0x38); // +0x38
      iVar1 = FUN_00471610();
      uStack_34 = *(undefined8 *)(iVar1 + 0x30);
      uStack_2c = *(undefined4 *)(iVar1 + 0x38);
      if (iStack_44 != 0) {
        FUN_004daf90(&iStack_44); // Release reference
        iStack_44 = 0;
      }
      if (iStack_3c != 0) {
        FUN_004daf90(&iStack_3c);
        iStack_3c = 0;
      }
    }
    else {
      iVar1 = FUN_00471610();
      uStack_28 = *(undefined8 *)(iVar1 + 0x30);
      uStack_20 = *(undefined4 *)(iVar1 + 0x38);
      iVar1 = FUN_00471610();
      uStack_34 = *(undefined8 *)(iVar1 + 0x30);
      uStack_2c = *(undefined4 *)(iVar1 + 0x38);
      iVar1 = param_3 + 0x48; // param_3 is likely a pointer to some object, +0x48 is a field
      if (iStack_3c != iVar1) {
        if (iStack_3c != 0) {
          FUN_004daf90(&iStack_3c); // Release reference
        }
        iStack_3c = iVar1;
        if (iVar1 != 0) {
          uStack_38 = *(undefined4 *)(param_3 + 0x4c); // +0x4C
          *(int **)(param_3 + 0x4c) = &iStack_3c;
        }
      }
      iVar1 = iStack_3c;
      if (iStack_44 != iStack_3c) {
        if (iStack_44 != 0) {
          FUN_004daf90(&iStack_44);
        }
        iStack_44 = iVar1;
        if (iVar1 != 0) {
          uStack_40 = *(undefined4 *)(iVar1 + 4);
          *(int **)(iVar1 + 4) = &iStack_44;
        }
      }
      if (param_4 != 0) {
        FUN_0044b210(param_4); // Some cleanup/release function
      }
    }
    fVar2 = (float10)(**(code **)(*this + 0xc0))();
    uStack_10 = 6; // Default state/action
    if ((float10)fStack_4c <= fVar2) {
      uStack_10 = 2; // Different state if regen amount is small
    }
    FUN_00408bb0(&DAT_0112dd94, this + 0xf, auStack_48, 0); // Send event/message
    if (iStack_3c != 0) {
      FUN_004daf90(&iStack_3c);
    }
    if (iStack_44 != 0) {
      FUN_004daf90(&iStack_44);
    }
  }
  return;
}