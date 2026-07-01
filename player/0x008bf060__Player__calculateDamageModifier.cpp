// FUNC_NAME: Player::calculateDamageModifier
float __thiscall Player::calculateDamageModifier(int param_1, int param_2)
{
  float fVar1;
  int *piVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float local_8;
  
  local_8 = 0.0;
  iVar4 = FUN_006b4860(); // IsPlayerInVehicle?
  if (iVar4 == 0) {
    iVar4 = FUN_006b1a20(); // GetPlayerHealth
    iVar5 = FUN_006b1a40(); // GetPlayerArmor
    fVar3 = (float)(iVar4 + iVar5); // health + armor
    if (iVar4 + iVar5 < 0) {
      fVar3 = fVar3 + DAT_00e44578; // Handle negative sum
    }
    if (*(int *)(param_2 + 0xc4) != 1) { // param_2+0xC4: damageType != 1 (not melee?)
      fVar1 = *(float *)(param_2 + 0xd0); // param_2+0xD0: damageMultiplier
      iVar4 = FUN_008bece0(); // GetRandomFloat?
      fVar6 = (float10)iVar4;
      if (iVar4 < 0) {
        fVar6 = fVar6 + (float10)DAT_00e44578;
      }
      return fVar6 * (float10)fVar1 + (float10)fVar3; // random * multiplier + health+armor
    }
    piVar2 = *(int **)(param_2 + 0xc0); // param_2+0xC0: damageSource
    fVar6 = (float10)FUN_0084a820(*(undefined4 *)(param_1 + 0x54)); // GetWeaponDamage
    local_8 = (float)(fVar6 * (float10)*(float *)(*(int *)(param_1 + 0x1d0) + 0x1c) *
                      (float10)*(float *)(DAT_0112f938 + 0x14) + (float10)fVar3);
    iVar4 = FUN_0084a430(); // GetCurrentWeapon?
    if ((iVar4 != 0) && (iVar4 = FUN_0084a430(), iVar4 != *(int *)(param_1 + 0x54))) {
      local_8 = *(float *)(*(int *)(param_1 + 0x1d0) + 0x24) * *(float *)(DAT_0112f938 + 0x30) +
                local_8;
    }
    local_8 = *(float *)(*piVar2 + 0x50) + local_8; // Add base damage from damage source
  }
  return (float10)local_8;
}