// FUNC_NAME: PlayerSM::updateAimAssist
void __fastcall PlayerSM::updateAimAssist(int *this)
{
  int iVar1;
  int iVar2;
  char cVar3;
  float10 fVar4;
  float fVar5;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  cVar3 = FUN_004ac260(); // IsGamePaused?
  if (cVar3 != '\0') {
    this[0x2b] = this[0x2b] | 2; // Set some flag at +0xAC
  }
  iVar1 = this[0x16]; // +0x58 - likely player entity pointer
  if ((*(uint *)(iVar1 + 0x8e0) >> 1 & 1) == 0) { // Check if aim assist is disabled
    iVar2 = this[0x25]; // +0x94 - current weapon index
    local_14 = _DAT_00d5780c; // Some global constant (likely 0.0f)
    local_18 = _DAT_00d5780c;
    fVar5 = _DAT_00d5780c;
    FUN_007d0640(iVar2, &local_14, &local_18); // Get weapon aim parameters
    iVar1 = *(int *)(iVar1 + 0x218); // +0x218 - current target entity
    if (iVar1 != 0) {
      iVar1 = *(int *)(iVar1 + 0x14); // +0x14 - target type/hash
      if ((((iVar2 == 1) && (iVar1 != -0x4225ea8e)) || ((iVar2 == 2 && (iVar1 != 0x3b1716f0)))) ||
         ((iVar2 == 3 && (iVar1 != -0x289a7ddf)))) {
        local_10 = fVar5;
        local_c = fVar5;
        FUN_007d0640(this[0x26], &local_10, &local_c); // Get alternate weapon aim params
        if ((iVar1 == 0x46f5c7b4) ||
           (((iVar1 == -0x4225ea8e || (iVar1 == 0x3b1716f0)) || (iVar1 == -0x289a7ddf)))) {
          local_14 = local_10;
          local_18 = local_c;
        }
        else {
          fVar4 = (float10)FUN_0045fa40(); // Random float 0-1
          local_8 = (float)fVar4;
          fVar4 = (float10)FUN_0045fa60(); // Another random float
          local_4 = (float)fVar4;
          if ((float10)DAT_00e44598 < fVar4) { // Compare with some threshold
            local_14 = (local_14 - local_10) * (local_8 / local_4) + local_10;
            local_18 = (local_18 - local_c) * (local_8 / local_4) + local_c;
          }
        }
      }
      else {
        this[0x26] = iVar2; // +0x98 - set alternate weapon to current
      }
    }
    // Call virtual function at vtable+0x2C (likely SetAimAssist or similar)
    (**(code **)(*this + 0x2c))(0x20391f0e, 1, 0, 0, local_14, local_18);
  }
  else {
    // Aim assist disabled - call with different parameters
    (**(code **)(*this + 0x2c))(0x8f2d9a2e, 1, 0, 0, 0x3f800000, _DAT_00e52fcc);
  }
  // Call virtual function at player entity vtable+0x164 (likely update animation/state)
  (**(code **)(*(int *)this[0x16] + 0x164))();
  return;
}