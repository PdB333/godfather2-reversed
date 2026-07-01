// FUNC_NAME: PlayerCCTVariables::updateCrouchState
void __thiscall PlayerCCTVariables::updateCrouchState(int this, float *param_2, undefined4 param_3, undefined4 param_4, float param_5)
{
  bool bVar1;
  char cVar2;
  bool bVar3;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  // Get current velocity and position vectors
  FUN_00864890(&local_28, &local_1c);
  // Calculate displacement from current position to target position (offsets +0xfe0, +0xfe4, +0xfe8)
  local_24 = *(float *)(this + 0xfe4) - local_24;
  local_20 = *(float *)(this + 0xfe8) - local_20;
  local_28 = *(float *)(this + 0xfe0) - local_28;
  // Compute distance to target
  local_2c = SQRT(local_20 * local_20 + local_24 * local_24 + local_28 * local_28);
  // Check if moving towards target (dot product of velocity and displacement)
  bVar3 = local_18 * local_24 + local_1c * local_28 + local_14 * local_20 < 0.0;
  bVar1 = false;
  // Check crouch state flags at +0xf28 (bit 25 = 0x02000000)
  if ((*(uint *)(this + 0xf28) >> 0x19 & 1) == 0) {
LAB_00866158:
    // Check bit 26 = 0x04000000
    if ((*(uint *)(this + 0xf28) >> 0x1a & 1) == 0) goto LAB_0086620e;
  }
  else {
    cVar2 = FUN_008653f0(bVar3);
    if (cVar2 == '\0') {
      if (bVar3) {
        // Clear bits 25,26,27 (0x0e000000 mask)
        *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) & 0xd5ffffff;
        // Release animation handles at +0x1038 and +0x1044
        if (*(int *)(this + 0x1038) != 0) {
          FUN_004daf90((undefined4 *)(this + 0x1038));
          *(undefined4 *)(this + 0x1038) = 0;
        }
        *(undefined4 *)(this + 0x1040) = 0;
        if (*(int *)(this + 0x1044) != 0) {
          FUN_004daf90((undefined4 *)(this + 0x1044));
          *(undefined4 *)(this + 0x1044) = 0;
        }
        *(undefined4 *)(this + 0x104c) = 0;
      }
      goto LAB_00866158;
    }
    bVar1 = true;
  }
  if (bVar3) {
    local_2c = 0.0;
  }
  // Call movement function with distance
  cVar2 = FUN_0085fa40(param_2, param_3, param_4, local_2c, 0);
  // Check if moving away or speed below threshold
  if ((bVar3) || (param_5 < DAT_00d58cbc)) {
    if (bVar1) {
      bVar3 = (*(uint *)(this + 0xf28) >> 0x1b & 1) == 0;
    }
    else {
      // Check some timer at +0xf7c
      if (DAT_00e44868 < *(float *)(this + 0xf7c)) goto LAB_0086620e;
      *(undefined4 *)(this + 0xf7c) = 0;
      bVar3 = (*(uint *)(this + 0xf28) >> 0x1b & 1) == 0;
    }
  }
  else {
    if (cVar2 == '\0') goto LAB_0086620e;
    bVar3 = (*(uint *)(this + 0xf28) >> 0x1b & 1) == 0;
  }
  // Set bit 27 (0x08000000) if not already set
  if (bVar3) {
    *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) | 0x8000000;
  }
LAB_0086620e:
  // Clamp param_2 to maximum speed if bit 27 is set and speed exceeds limit
  if (((*(uint *)(this + 0xf28) >> 0x1b & 1) != 0) && (DAT_00d5f520 < *param_2)) {
    *param_2 = DAT_00d5f520;
  }
  return;
}