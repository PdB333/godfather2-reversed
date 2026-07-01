// FUNC_NAME: PlayerGroundSM::updateMovement
float __thiscall PlayerGroundSM::updateMovement(float *this, float param_2, undefined4 param_3)
{
  uint uVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  bool bVar7;
  bool bVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float local_18;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_18 = 0.0;
  // Check if bit 0 of flags at +0x48 is set (e.g., isDead or isDisabled)
  if (((uint)this[0x48] & 1) == 0) {
    fVar2 = 0.0;
    // Check if there are any active movement modifiers at +0x1C (this[7]) and +0x20 (this[8])
    if (this[8] != 0.0) {
      piVar6 = (int *)this[7];
      do {
        // Compare modifier ID with param_2's +0x50 (likely some object ID)
        if (*piVar6 == *(int *)((int)param_2 + 0x50)) goto LAB_0077e68e;
        fVar2 = (float)((int)fVar2 + 1);
        piVar6 = piVar6 + 2;
      } while ((uint)fVar2 < (uint)this[8]);
    }
  }
  // Call some initialization function with param_2
  FUN_0077e2f0(param_2);
  fVar2 = *this; // Store initial position at +0x00
  local_10 = 0.0;
  local_c = 0.0;
  local_8 = 0.0;
  local_4 = 0.0;
  // Get input values from param_3 (likely controller input)
  FUN_00728b20(&local_10, param_3);
  fVar13 = DAT_00d68ebc; // Some global max value (likely 1.0 or similar)
  // Apply input to movement axes (this[1] through this[4] are movement accumulators)
  if (local_10 != 0.0) {
    fVar11 = local_10 + this[1];
    this[1] = fVar11;
    if (0.0 < fVar11) {
      if (fVar13 <= fVar11) {
        fVar11 = fVar13;
      }
    }
    else {
      fVar11 = 0.0;
    }
    this[1] = fVar11;
  }
  if (local_c != 0.0) {
    fVar11 = this[2] + local_c;
    this[2] = fVar11;
    if (0.0 < fVar11) {
      if (fVar13 <= fVar11) {
        fVar11 = fVar13;
      }
    }
    else {
      fVar11 = 0.0;
    }
    this[2] = fVar11;
  }
  if (local_8 != 0.0) {
    fVar11 = this[3] + local_8;
    this[3] = fVar11;
    if (0.0 < fVar11) {
      if (fVar13 <= fVar11) {
        fVar11 = fVar13;
      }
    }
    else {
      fVar11 = 0.0;
    }
    this[3] = fVar11;
  }
  if (local_4 != 0.0) {
    fVar12 = this[4] + local_4;
    this[4] = fVar12;
    fVar11 = 0.0;
    if ((0.0 < fVar12) && (fVar11 = fVar12, fVar13 <= fVar12)) {
      fVar11 = fVar13;
    }
    this[4] = fVar11;
  }
  // Get some value from a function using this[0] (likely current position)
  uVar3 = FUN_00782400(*this);
  fVar9 = (float10)FUN_00728a80(uVar3, param_3);
  param_2 = (float)fVar9;
  bVar8 = true;
  fVar13 = DAT_00d68ebc;
  // Check if the value is above a threshold (DAT_00e44598)
  if ((float10)DAT_00e44598 < ABS(fVar9)) {
    do {
      if (!bVar8) break;
      iVar4 = FUN_00782400(*this + _DAT_00d68eb8); // Get next position index
      fVar9 = (float10)FUN_00728a80(iVar4, param_3);
      uVar1 = DAT_00e44680;
      fVar13 = DAT_00d68ebc;
      fVar11 = (float)fVar9;
      if (fVar9 < (float10)0) {
        // Negative case: moving backwards
        if ((fVar11 < param_2) && (fVar11 = param_2, 0.0 <= param_2)) {
          fVar11 = 0.0;
        }
        if (this[5] == 0.0) {
          iVar5 = 0;
        }
        else {
          iVar5 = (int)this[5] + -0x48; // Adjust pointer to some base
        }
        fVar10 = *this;
        fVar12 = *(float *)(iVar5 + 0x50 + iVar4 * 4) - (fVar10 + _DAT_00d68eb8);
        bVar8 = fVar10 == 0.0;
        bVar7 = fVar10 < 0.0;
      }
      else {
        // Positive case: moving forward
        if (0.0 < param_2) {
          if (fVar11 <= param_2) {
            param_2 = fVar11;
          }
        }
        else {
          param_2 = 0.0;
        }
        fVar12 = DAT_00d68ebc;
        if (iVar4 != 3) {
          if (this[5] == 0.0) {
            iVar5 = 0;
          }
          else {
            iVar5 = (int)this[5] + -0x48;
          }
          fVar12 = *(float *)(iVar5 + 0x54 + iVar4 * 4);
        }
        fVar10 = *this;
        fVar12 = fVar12 - fVar10;
        bVar8 = DAT_00d68ebc == fVar10;
        bVar7 = DAT_00d68ebc < fVar10;
        fVar11 = param_2;
      }
      bVar8 = !bVar7 && !bVar8;
      // Compare magnitudes using bitwise AND with mask
      if ((float)((uint)fVar11 & DAT_00e44680) <= (float)((uint)fVar12 & DAT_00e44680)) {
        *this = fVar10 + fVar11;
        param_2 = 0.0;
      }
      else {
        *this = fVar10 + fVar12;
        param_2 = fVar11 - fVar12;
        if (iVar4 != 3) {
          this[10] = DAT_01205228; // Set some flag at +0x28
        }
      }
    } while (DAT_00e44598 < (float)((uint)param_2 & uVar1));
  }
  // Clamp final position to [0, fVar13]
  local_18 = *this;
  if (0.0 < local_18) {
    if (fVar13 <= local_18) {
      local_18 = fVar13;
    }
  }
  else {
    local_18 = 0.0;
  }
  *this = local_18;
  local_18 = local_18 - fVar2; // Return delta movement
LAB_0077e68e:
  return (float10)local_18;
}