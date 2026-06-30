// FUNC_NAME: Player::updateMovement
char __thiscall Player::updateMovement(int this, int param_2)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  char local_4c;
  undefined4 local_48;
  int local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_14;

  cVar1 = FUN_00581f60(param_2); // Check if input is active
  if (*(char *)(param_2 + 0x10) != '\0') { // Check if input has movement data
    local_50 = 0;
    local_54 = (uint)(cVar1 != '\0') * 2 + -4;
    local_4c = '\0';
    local_48 = 0;
    local_5c = this;
    local_58 = this;
    iVar2 = FUN_00587a00(&local_5c); // Check if player is alive
    if (-1 < iVar2) {
      if (local_4c != '\0') {
        uStack_28 = 0;
        uStack_2c = 0;
        local_30 = 0;
        uStack_18 = 0;
        uStack_1c = 0;
        local_20 = 0;
        local_3c = *(undefined4 *)(this + 0x20); // +0x20: current position X
        local_38 = *(float *)(this + 0x24) - DAT_00e2b1a4; // +0x24: current position Y, subtract some constant
        fStack_24 = DAT_00e2b1a4;
        fStack_14 = DAT_00e2b1a4;
        local_40 = this;
        FUN_00581d70(&local_40); // Calculate movement vector
        *(undefined4 *)(this + 0x40) = local_30; // +0x40: velocity X
        *(undefined4 *)(this + 0x44) = uStack_2c; // +0x44: velocity Y
        *(undefined4 *)(this + 0x48) = uStack_28; // +0x48: velocity Z
        *(float *)(this + 0x4c) = fStack_24; // +0x4c: speed
        *(undefined4 *)(this + 0x50) = local_20; // +0x50: movement direction X
        *(undefined4 *)(this + 0x54) = uStack_1c; // +0x54: movement direction Y
        *(undefined4 *)(this + 0x58) = uStack_18; // +0x58: movement direction Z
        *(float *)(this + 0x5c) = fStack_14; // +0x5c: movement magnitude
        uVar3 = FUN_00579870(); // Get current time
        FUN_00579450(this, uVar3); // Update animation
        *(uint *)(this + 0x10) = *(uint *)(this + 0x10) | 1; // +0x10: set movement flag
        *(float *)(this + 0x1c) = *(float *)(param_2 + 8) + *(float *)(this + 0x1c); // +0x1c: update movement timer
        return cVar1;
      }
      uVar3 = FUN_00579870();
      FUN_00579450(this, uVar3);
    }
  }
  return cVar1;
}