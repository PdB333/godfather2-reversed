// FUNC_NAME: PlayerCCTVariables::applyInputVelocity
void __thiscall PlayerCCTVariables::applyInputVelocity(int this, float *inputVelocity)
{
  float fVar1;
  float fVar2;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  // +0x3a: bool flag indicating some special state (e.g. sprinting, crouching)
  // _DAT_00d5780c: base speed multiplier (global)
  // DAT_00d5eea0: alternate speed multiplier (used when flag is set)
  local_18 = _DAT_00d5780c;
  if (*(char *)(this + 0x3a) != '\0') {
    local_18 = DAT_00d5eea0;
  }
  
  // DAT_0112a6f4: maximum velocity magnitude clamp (global)
  if (DAT_0112a6f4 <= 0.0) {
    // No clamping - directly apply scaled velocity
    // +0x40: velocity.x, +0x44: velocity.y, +0x48: velocity.z
    *(float *)(this + 0x40) = *inputVelocity * local_18;
    *(float *)(this + 0x44) = inputVelocity[1] * local_18;
    *(float *)(this + 0x48) = inputVelocity[2] * local_18;
  }
  else {
    // Clamp velocity magnitude to DAT_0112a6f4
    fVar2 = inputVelocity[1] * local_18;
    local_20 = *inputVelocity * local_18;
    local_18 = inputVelocity[2] * local_18;
    // DAT_00e44564: negative clamp bound (likely -maxVelocity)
    local_1c = DAT_00e44564 - DAT_0112a6f4;
    if ((local_1c <= fVar2) && (local_1c = fVar2, DAT_0112a6f4 < fVar2)) {
      local_1c = DAT_0112a6f4;
    }
    local_14 = 0;
    // FUN_0056afa0: likely vector length squared (or dot product with self)
    fVar1 = (float10)FUN_0056afa0(&local_20, &local_20);
    if ((float10)0 < fVar1) {
      // Store clamped velocity (y component clamped, x and z as-is)
      *(ulonglong *)(this + 0x40) = CONCAT44(local_1c, local_20);
      *(float *)(this + 0x48) = local_18;
      return;
    }
  }
  return;
}