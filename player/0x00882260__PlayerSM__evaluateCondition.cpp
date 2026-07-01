// FUNC_NAME: PlayerSM::evaluateCondition
undefined1 __thiscall PlayerSM::evaluateCondition(int *this, undefined4 param_2, undefined4 param_3, int conditionId, undefined4 param_5)
{
  char cVar1;
  undefined1 result;
  int iVar3;
  float unaff_EBX;
  float10 extraout_ST0;
  float10 fVar4;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float fVar5;
  float fVar6;
  float fVar7;
  float local_c;
  float fStack_8;
  
  result = 0;
  switch(conditionId + -10) {
  case 0: // Condition 10: Is climbing? Check ragdoll state
    // +0x1a = mRagdollComponent pointer, +0xf2c = mIsClimbing flag
    return *(int *)(this[0x1a] + 0xf2c) == 1;
  case 1: // Condition 11: Distance to player less than threshold
    iVar3 = FUN_00471610(); // Get player transform
    fVar6 = (float)this[0x1b] - *(float *)(iVar3 + 0x30); // this X vs player X
    fVar5 = (float)this[0x1c] - *(float *)(iVar3 + 0x34); // this Y vs player Y
    fVar7 = (float)this[0x1d] - *(float *)(iVar3 + 0x38); // this Z vs player Z
    if (fVar7 * fVar7 + fVar5 * fVar5 + fVar6 * fVar6 < DAT_00d76e6c) { // SQUARED_DIST_THRESHOLD
      return true;
    }
    return false;
  case 2: // Condition 12: Not in cover
    // +0x1e = mCoverState flags, bit 1 = is in cover
    return ~(byte)((uint)this[0x1e] >> 1) & 1;
  case 3: // Condition 13: In cover
    return (byte)((uint)this[0x1e] >> 1) & 1;
  default:
    result = FUN_004ac640(param_2,param_3,conditionId,param_5); // Base class condition handler
    break;
  case 5: // Condition 15: Is grounded?
    // +0x1e low bit = isGrounded
    return *(byte *)(this + 0x1e) & 1;
  case 6: // Condition 16: Time since last condition change less than threshold
    // Call getElapsedTime on sentient
    (**(code **)(*(int *)this[0x1a] + 0x1b0))(); // Get elapsed time since last state change
    fVar4 = extraout_ST0;
    goto LAB_008822ed;
  case 7: // Condition 17: Near player within interaction range
    if ((*(int *)(this[0x1a] + 0xaa0) != 0) && (cVar1 = FUN_0085e970(), cVar1 != '\0')) { // Is valid? and interaction check
      iVar3 = FUN_00471610(); // Get player transform
      FUN_0045c470(this + 0x1b, iVar3 + 0x30); // Vector subtract
      if (extraout_ST0_00 < (float10)DAT_00d76e74) { // INTERACTION_RANGE_SQ
        return true;
      }
      cVar1 = (**(code **)(*this + 0x30))(&local_c); // Get interaction target position
      if ((cVar1 != '\0') &&
         (iVar3 = FUN_00471610(), fVar6 = unaff_EBX - *(float *)(iVar3 + 0x30),
         local_c = local_c - *(float *)(iVar3 + 0x34),
         fStack_8 = fStack_8 - *(float *)(iVar3 + 0x38),
         fStack_8 * fStack_8 + local_c * local_c + fVar6 * fVar6 < DAT_00d76e74)) { // INTERACTION_RANGE_SQ
        return true;
      }
    }
    break;
  case 8: // Condition 18: In combat state?
    // +0x1190 = mCombatState
    if (*(int *)(this[0x1a] + 0x1190) == 3) {
      return true;
    }
    break;
  case 9: // Condition 19: Is witness checking?
    iVar3 = FUN_008752d0(); // Is witness present check
    if (iVar3 == 0) {
      return true;
    }
    break;
  case 10: // Condition 20: Action cooldown timer check
    // +0x3ca (word offset) = mActionCooldownFlags
    if (((uint)((int *)this[0x1a])[0x3ca] >> 0xe & 1) == 0) {
      return false;
    }
    (**(code **)(*(int *)this[0x1a] + 0x1b0))(); // Get elapsed time
    fVar4 = extraout_ST0_01;
LAB_008822ed:
    if (fVar4 < (float10)_DAT_00d76e68) { // COOLDOWN_TIME
      return true;
    }
    return false;
  }
  return result;
}