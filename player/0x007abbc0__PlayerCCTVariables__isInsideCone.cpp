// FUNC_NAME: PlayerCCTVariables::isInsideCone
undefined4 PlayerCCTVariables::isInsideCone(float *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  undefined1 local_50 [12];
  undefined4 local_44;
  undefined4 local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_14;
  
  iVar1 = FUN_00471610(); // Get player position
  local_60 = *param_1 - *(float *)(iVar1 + 0x30); // dx = target.x - player.x
  local_5c = param_1[1] - *(float *)(iVar1 + 0x34); // dy = target.y - player.y
  local_58 = param_1[2] - *(float *)(iVar1 + 0x38); // dz = target.z - player.z
  local_54 = 0;
  FUN_0056afa0(&local_60,&local_60); // Normalize direction vector
  iVar1 = FUN_00471610(); // Get player position again
  iVar2 = FUN_00471610(); // Get player facing direction
  iVar3 = FUN_00471610(); // Get player position again
  fVar4 = *(float *)(iVar2 + 0x24) * local_5c + local_60 * *(float *)(iVar1 + 0x20) +
          *(float *)(iVar3 + 0x28) * local_58; // Dot product with facing direction
  if (_DAT_00d577a0 < fVar4) { // Check if within cone angle (cosine threshold)
    FUN_00425060(&local_78,0); // Get cone origin
    FUN_00424fb0(&local_6c,0); // Get cone direction
    local_44 = 0;
    local_34 = 0;
    local_24 = 0;
    local_14 = _DAT_00d5780c; // Cone length
    FUN_0056b8a0(local_74,local_78,local_70,local_50); // Transform to cone space
    if ((local_5c * local_2c + local_60 * local_30 + local_58 * local_28 < fVar4) &&
       (_DAT_00d577a0 <
        local_5c * (param_1[1] - local_68) + local_60 * (*param_1 - local_6c) +
        local_58 * (param_1[2] - local_64))) {
      return 1; // Inside cone
    }
  }
  return 0; // Outside cone
}