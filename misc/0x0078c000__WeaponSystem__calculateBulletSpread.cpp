// FUNC_NAME: WeaponSystem::calculateBulletSpread
void __thiscall WeaponSystem::calculateBulletSpread(int this, float param_2, float param_3, float param_4, float *outSpread)
{
  int iVar1;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined8 local_2c;
  float local_24;
  undefined8 local_20;
  float local_18;
  undefined4 local_14;
  
  iVar1 = FUN_00471610(); // Get player camera
  local_20 = *(undefined8 *)(iVar1 + 0x30); // Camera forward vector (x,z)
  local_18 = *(float *)(iVar1 + 0x38); // Camera forward y component
  iVar1 = FUN_00471610(); // Get player camera again
  local_24 = *(float *)(iVar1 + 0x38); // Camera position y
  local_2c = *(undefined8 *)(iVar1 + 0x30); // Camera position (x,z)
  iVar1 = _rand();
  local_3c = (float)iVar1 * DAT_00e44590 * param_4 * DAT_00e445c8; // Random spread factor
  if (*(int *)(this + 0x18) == 1) { // Check weapon type (1 = shotgun)
    local_3c = local_3c * DAT_00d5ccf8; // Additional shotgun spread multiplier
  }
  local_38 = (float)local_20 - (float)local_2c; // Direction vector x
  local_30 = local_18 - local_24; // Direction vector y
  local_34 = 0.0;
  local_20 = (ulonglong)(uint)local_38;
  local_14 = 0;
  local_18 = local_30;
  FUN_0056afa0(&local_20,&local_20); // Normalize direction vector
  local_38 = (float)local_20;
  local_34 = local_20._4_4_;
  local_30 = local_18;
  FUN_004a0370(&local_38,&local_38,&DAT_00d69a38,local_3c); // Apply spread rotation
  *outSpread = local_38 * param_3 + (float)local_2c; // Final spread x
  outSpread[1] = local_34 * param_3 + local_2c._4_4_; // Final spread z
  outSpread[2] = local_30 * param_3 + local_24; // Final spread y
  return;
}