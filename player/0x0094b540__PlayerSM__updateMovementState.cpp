// FUNC_NAME: PlayerSM::updateMovementState
undefined4 __thiscall PlayerSM_updateMovementState(int this, undefined4 param_2, undefined4 param_3, float param_4, float param_5, float param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9, undefined4 param_10, undefined4 param_11)
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  float fVar4;
  float local_3c;
  float local_38;
  float local_30;
  float local_2c;
  float local_24;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  // Check bit 0x11 (17) of flags at +0x11c
  if ((*(uint *)(this + 0x11c) >> 0x11 & 1) == 0) {
    // Check bit 0x12 (18) of flags
    if ((*(uint *)(this + 0x11c) >> 0x12 & 1) == 0) {
      return 1;
    }
    return 0;
  }
  
  FUN_009498a0(); // Likely some state entry/exit function
  
  iVar2 = *(int *)(this + 0x118); // Movement state type at +0x118
  if (iVar2 == 3) { // State 3: Direct movement (e.g., teleport)
    local_38 = param_4;
    local_3c = param_5;
    switch(*(undefined4 *)(this + 0x170)) { // Direction at +0x170
    case 0: // Up
      local_3c = param_5 - param_6;
      break;
    case 1: // Down
      local_3c = param_5 + param_6;
      break;
    case 2: // Left
      local_38 = param_4 - param_6;
      break;
    case 3: // Right
      local_38 = param_4 + param_6;
    }
    FUN_0094a250(local_38, local_3c, param_7); // Set position
    goto LAB_0094b95f;
  }
  
  if (iVar2 == 1) { // State 1: Ground movement
    if ((*(int *)(this + 0x154) == 0) || (*(int *)(this + 0x154) == 0x48)) { // Check some state at +0x154
      uVar3 = *(uint *)(this + 0x11c);
LAB_0094b799:
      if (((uVar3 >> 3 & 1) != 0) && ((uVar3 >> 0x10 & 1) == 0)) {
LAB_0094b7a2:
        FUN_0094aca0(); // Handle some animation/state
      }
    }
    else {
      iVar2 = FUN_00471610(); // Get some object
      fVar4 = _DAT_00d5780c; // Global time delta
      *(undefined4 *)(this + 0x130) = *(undefined4 *)(iVar2 + 0x30); // Copy velocity
      *(undefined4 *)(this + 0x134) = *(undefined4 *)(iVar2 + 0x34);
      uVar1 = *(undefined4 *)(iVar2 + 0x38);
      *(float *)(this + 0x13c) = fVar4;
      *(undefined4 *)(this + 0x138) = uVar1;
    }
  }
  else if (iVar2 == 4) { // State 4: Air movement
    if ((*(int *)(this + 0x15c) == 0) || (*(int *)(this + 0x15c) == 0x48)) {
LAB_0094b78b:
      uVar3 = *(uint *)(this + 0x11c);
      goto LAB_0094b799;
    }
    if (*(int *)(this + 0x15c) == 0) {
      iVar2 = FUN_00790cd0(); // Get some object
    }
    else {
      iVar2 = FUN_00790cd0();
    }
LAB_0094b779:
    FUN_00424680(this + 0x130, iVar2); // Copy vector
  }
  else if (iVar2 == 5) { // State 5: Climbing/ladder
    if (((*(int *)(this + 0x15c) == 0) || (*(int *)(this + 0x15c) == 0x48)) ||
       (iVar2 = FUN_00791300(), iVar2 == 0)) {
      if (((*(int *)(this + 0x15c) == 0) || (*(int *)(this + 0x15c) == 0x48)) &&
         (((*(uint *)(this + 0x11c) >> 3 & 1) != 0 &&
          ((*(uint *)(this + 0x11c) >> 0x10 & 1) == 0)))) goto LAB_0094b7a2;
      if ((*(uint *)(this + 0x11c) >> 0x1d & 1) != 0) {
        *(undefined4 *)(this + 0x130) = *(undefined4 *)(this + 0x1f0); // Copy from some other vector
        *(undefined4 *)(this + 0x134) = *(undefined4 *)(this + 500);
        *(undefined4 *)(this + 0x138) = *(undefined4 *)(this + 0x1f8);
        *(undefined4 *)(this + 0x13c) = *(undefined4 *)(this + 0x1fc);
      }
    }
    else {
      FUN_00791300();
      iVar2 = FUN_00471610();
      FUN_00424680(this + 0x130, iVar2 + 0x30); // Copy velocity from object
    }
  }
  else if (iVar2 == 2) { // State 2: Swimming
    if ((*(int *)(this + 0x168) == 0) || (*(int *)(this + 0x168) == 0x48)) goto LAB_0094b78b;
    iVar2 = FUN_00950b20(); // Check some condition
    if (iVar2 != 0) goto LAB_0094b779;
  }
  
  // Calculate new position based on velocity and delta time
  local_20 = *(float *)(this + 0x140) + *(float *)(this + 0x130); // position + velocity
  fStack_1c = *(float *)(this + 0x144) + *(float *)(this + 0x134);
  fStack_18 = *(float *)(this + 0x148) + *(float *)(this + 0x138);
  fStack_14 = *(float *)(this + 0x14c) + *(float *)(this + 0x13c);
  
  FUN_0056b420(param_2, &local_20, &local_30); // Transform to world space
  
  if (local_24 != _DAT_00d577a0) { // Check for valid result
    uVar3 = *(uint *)(this + 0x11c);
    fVar4 = _DAT_00d5780c / (float)((uint)local_24 & DAT_00e44680); // Some scaling factor
    local_3c = fVar4 * local_30 * param_6; // Movement delta Y
    local_38 = (DAT_00e44564 - fVar4 * local_2c) * param_6; // Movement delta X
    
    fVar4 = SQRT(local_38 * local_38 + local_3c * local_3c); // Calculate movement magnitude
    
    if ((((uVar3 >> 5 & 1) != 0) || ((uVar3 >> 4 & 1) != 0)) || (fVar4 <= param_6)) {
      if ((uVar3 >> 0x14 & 1) != 0) {
        FUN_00949850(); // Clear some state
        *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) & 0xffefffff;
      }
      if ((((*(uint *)(this + 0x11c) >> 4 & 1) != 0) || (param_6 < fVar4)) &&
         (fVar4 != _DAT_00d577a0)) {
        // Clamp movement to max speed
        local_3c = (param_6 / fVar4) * local_3c;
        local_38 = (param_6 / fVar4) * local_38;
      }
      FUN_00949960(param_3, &local_20); // Update some transform
      FUN_0094a250(local_3c + param_4, local_38 + param_5, param_7); // Set new position
      FUN_00948c60(param_10); // Handle collision
      if ((*(uint *)(this + 0x11c) >> 6 & 1) != 0) {
        FUN_0094b320(); // Additional movement handling
      }
    }
    else if ((uVar3 >> 0x14 & 1) == 0) {
      FUN_00949800(); // Set some state
      *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) | 0x100000;
    }
  }
  
LAB_0094b95f:
  FUN_0094a610(param_8, 0); // Update animation
  FUN_0094a6d0(param_11, param_3); // Update some transform
  FUN_00949900(param_9); // Finalize state
  return 1;
}