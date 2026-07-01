// FUNC_NAME: Player::updateCameraShake
void __fastcall Player::updateCameraShake(int this)
{
  float fVar1;
  float fVar2;
  float local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  fVar1 = *(float *)(this + 0x204); // +0x204: camera shake X offset
  fVar2 = *(float *)(this + 0x208); // +0x208: camera shake Y offset
  
  // Clamp and set global shake parameters (likely for screen shake effect)
  if (DAT_012058d0 < 7) {
    DAT_012058d0 = 7;
  }
  if (7 < DAT_00f15988) {
    DAT_00f15988 = 7;
  }
  _DAT_011f39f4 = 0;
  
  if (DAT_012058d0 < 0xe) {
    DAT_012058d0 = 0xe;
  }
  if (0xe < DAT_00f15988) {
    DAT_00f15988 = 0xe;
  }
  _DAT_011f3a10 = 0;
  
  if (DAT_012058d0 < 0x1b) {
    DAT_012058d0 = 0x1b;
  }
  if (0x1b < DAT_00f15988) {
    DAT_00f15988 = 0x1b;
  }
  _DAT_011f3a44 = 1;
  
  FUN_00417cf0(1,5,6); // Likely sets some camera shake parameters
  
  if (DAT_012058d0 < 0x19) {
    DAT_012058d0 = 0x19;
  }
  if (0x19 < DAT_00f15988) {
    DAT_00f15988 = 0x19;
  }
  _DAT_011f3a3c = 7;
  
  if (DAT_012058d0 < 0x18) {
    DAT_012058d0 = 0x18;
  }
  if (0x18 < DAT_00f15988) {
    DAT_00f15988 = 0x18;
  }
  _DAT_011f3a38 = 0;
  
  if (DAT_012058d0 < 0xf) {
    DAT_012058d0 = 0xf;
  }
  if (0xf < DAT_00f15988) {
    DAT_00f15988 = 0xf;
  }
  _DAT_011f3a14 = 0;
  
  DAT_011f4234 = 0;
  
  // Calculate shake offset with time factor
  local_60 = DAT_00d5eee4 / (float)DAT_0120587c + fVar1; // DAT_00d5eee4 likely time delta, DAT_0120587c some divisor
  local_5c = *(float *)(this + 0x20c) + fVar2; // +0x20c: another shake component
  
  // Initialize 16-element vector with a constant (likely zero or identity)
  local_50 = _DAT_00d5780c;
  local_4c = _DAT_00d5780c;
  local_48 = _DAT_00d5780c;
  local_44 = _DAT_00d5780c;
  local_40 = _DAT_00d5780c;
  local_3c = _DAT_00d5780c;
  local_38 = _DAT_00d5780c;
  local_34 = _DAT_00d5780c;
  local_30 = _DAT_00d5780c;
  local_2c = _DAT_00d5780c;
  local_28 = _DAT_00d5780c;
  local_24 = _DAT_00d5780c;
  local_20 = _DAT_00d5780c;
  local_1c = _DAT_00d5780c;
  local_18 = _DAT_00d5780c;
  local_14 = _DAT_00d5780c;
  
  local_68 = 0;
  local_64 = _DAT_00d5780c;
  local_58 = 0;
  local_54 = _DAT_00d5780c;
  
  local_70 = fVar1;
  local_6c = fVar2;
  
  FUN_006103f0(&local_70, &local_50, 0); // Likely applies shake to camera transform
  
  // Reset shake parameters after application
  if (DAT_012058d0 < 0x1b) {
    DAT_012058d0 = 0x1b;
  }
  if (0x1b < DAT_00f15988) {
    DAT_00f15988 = 0x1b;
  }
  _DAT_011f3a44 = 0;
  
  FUN_00417cf0(1,5,6);
  
  if (DAT_012058d0 < 0x19) {
    DAT_012058d0 = 0x19;
  }
  if (0x19 < DAT_00f15988) {
    DAT_00f15988 = 0x19;
  }
  _DAT_011f3a3c = 7;
  
  if (DAT_012058d0 < 0x18) {
    DAT_012058d0 = 0x18;
  }
  if (0x18 < DAT_00f15988) {
    DAT_00f15988 = 0x18;
  }
  _DAT_011f3a38 = 0;
  
  if (DAT_012058d0 < 0xf) {
    DAT_012058d0 = 0xf;
  }
  if (0xf < DAT_00f15988) {
    DAT_00f15988 = 0xf;
  }
  _DAT_011f3a14 = 0;
  
  if (DAT_012058d0 < 7) {
    DAT_012058d0 = 7;
  }
  if (7 < DAT_00f15988) {
    DAT_00f15988 = 7;
  }
  _DAT_011f39f4 = 1;
  
  if (DAT_012058d0 < 0xe) {
    DAT_012058d0 = 0xe;
  }
  _DAT_011f3a10 = 1;
  if (0xe < DAT_00f15988) {
    DAT_00f15988 = 0xe;
  }
  return;
}