// FUNC_NAME: Player::applyGravity
void Player::applyGravity(int param_1, undefined4 param_2, float *param_3)
{
  undefined4 *puVar1;
  float local_190;
  float fStack_18c;
  float fStack_188;
  float fStack_184;
  undefined4 local_180;
  float fStack_17c;
  undefined4 local_178;
  float local_174;
  undefined4 local_170;
  float local_16c;
  undefined4 local_168;
  undefined4 local_15c;
  float fStack_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 local_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 local_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 local_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  float fStack_114;
  undefined **local_110;
  float local_10c;
  float local_f0;
  undefined4 local_ec;
  undefined4 local_e0;
  undefined4 local_c0;
  int local_b0;
  undefined1 local_a0 [4];
  float local_9c;
  undefined1 local_50 [76];
  
  puVar1 = (undefined4 *)FUN_00471610(); // Get player's current transform matrix
  local_150 = *puVar1;
  uStack_14c = puVar1[1];
  uStack_148 = puVar1[2];
  local_140 = puVar1[4];
  uStack_13c = puVar1[5];
  uStack_138 = puVar1[6];
  local_130 = puVar1[8];
  uStack_12c = puVar1[9];
  uStack_128 = puVar1[10];
  local_120 = puVar1[0xc];
  uStack_11c = puVar1[0xd];
  uStack_118 = puVar1[0xe];
  uStack_144 = 0;
  uStack_134 = 0;
  uStack_124 = 0;
  fStack_188 = *(float *)(param_1 + 0x104); // Player's mass or gravity scale
  local_190 = fStack_188 * *param_3;
  fStack_18c = fStack_188 * param_3[1];
  fStack_188 = fStack_188 * param_3[2];
  fStack_114 = _DAT_00d5780c; // Global gravity constant
  fStack_184 = _DAT_00d5780c;
  FUN_0056b420(&local_150,&local_190,&local_170); // Transform velocity by matrix
  local_174 = *(float *)(param_1 + 0x104); // Mass/gravity scale again
  local_180 = local_170;
  fStack_17c = local_174 * DAT_00d5c454 + local_16c; // Apply gravity acceleration
  local_178 = local_168;
  local_154 = local_168;
  _local_15c = CONCAT44(fStack_17c - local_174,local_170);
  FUN_00542650(&local_180,&local_15c,0x60122,0x10000,0,0); // Raycast for ground collision
  local_ec = 0xffffffff;
  local_e0 = 0xffffffff;
  local_110 = &PTR_FUN_00e32a8c;
  local_b0 = 0;
  local_f0 = _DAT_00d5780c;
  local_c0 = 0;
  local_10c = _DAT_00d5780c;
  FUN_009e5ed0(local_a0,&local_110); // Check if grounded
  if (local_b0 != 0) {
    local_16c = local_9c - local_f0 * local_174;
    FUN_006e3b00(); // Handle landing
    FUN_0056b420(local_50,&local_170,&local_190); // Adjust velocity
    param_3[1] = *(float *)(param_1 + 0x108) * fStack_18c; // Apply friction
    return;
  }
  param_3[1] = param_3[1] - DAT_00d5842c; // Apply air resistance
  return;
}