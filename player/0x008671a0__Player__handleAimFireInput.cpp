// FUNC_NAME: Player::handleAimFireInput
char __fastcall Player::handleAimFireInput(int thisPtr)
{
  float local_c[3];
  float local_18[3];
  float local_1c;
  float local_10;
  float local_8;
  float local_4;
  char result;
  int iVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  bool bVar8;
  float10 fVar9;
  float10 extraout_ST0;

  result = '\0';
  // Check if player is dead or in a state that prevents aiming (bit 0x400000 at +0xf28)
  if (((*(uint *)(thisPtr + 0xf28) >> 0x16 & 1) != 0) ||
     (_DAT_00d577a0 < *(float *)(thisPtr + 0x1018))) {
    return '\0';
  }
  // Check if some global condition prevents aiming (e.g., cutscene playing)
  if (FUN_008603b0() != '\0') {
    return '\0';
  }
  // Get camera forward direction (likely from camera manager)
  FUN_00601970(*(undefined4 *)(thisPtr + 0x1148), &local_c);
  // Get player's facing direction (likely from transform)
  iVar4 = FUN_00471610(); // Get player transform
  iVar5 = FUN_00471610(); // Get player transform
  iVar6 = FUN_00471610(); // Get player transform
  // Check if player is facing away from camera (dot product with camera forward)
  if (DAT_00d62364 <
      *(float *)(iVar5 + 0x24) * local_8 + *(float *)(iVar4 + 0x20) * local_c +
      *(float *)(iVar6 + 0x28) * local_4) {
    return '\0';
  }
  local_1c = *(float *)(thisPtr + 0xfc4); // Some aim-related parameter
  // Check if we have a valid target (bit 0x7fffffff at +0xfd4)
  if (1 < (*(uint *)(thisPtr + 0xfd4) & 0x7fffffff)) {
    bVar8 = *(int *)(thisPtr + 0xfd0) == 0;
    FUN_008655d0(bVar8, &local_18); // Get target position
    if (FUN_00864d70(&local_18) != '\0') { // Check if target is valid
      fVar9 = (float10)FUN_0085ec00(bVar8, *(uint *)(thisPtr + 0xfd4) & 0x7fffffff,
                                    *(uint *)(thisPtr + 0xfd4) >> 0x1f);
      local_1c = (float)fVar9;
      goto LAB_0086736c;
    }
  }
  // No target, use camera aim direction
  iVar4 = FUN_00471610(); // Get camera
  FUN_008655a0(iVar4 + 0x30, &local_18); // Get camera aim direction
  if (((float10)0 <= extraout_ST0) && ((*(uint *)(thisPtr + 0xf28) >> 0x17 & 1) == 0)) {
    pfVar7 = (float *)FUN_00471610(); // Get player movement direction
    local_18 = *pfVar7 * DAT_00d5eee4 + local_18;
    fStack_14 = pfVar7[1] * DAT_00d5eee4 + fStack_14;
    local_10 = pfVar7[2] * DAT_00d5eee4 + local_10;
    if (FUN_00864d70(&local_18) == '\0') {
      return '\0';
    }
    local_1c = DAT_00e44750; // Default aim distance
  }
  if (result == '\0') {
    return '\0';
  }
LAB_0086736c:
  // Store aim direction and distance
  *(ulonglong *)(thisPtr + 0x101c) = CONCAT44(fStack_14, local_18);
  *(float *)(thisPtr + 0xfc8) = local_1c; // Aim distance
  *(float *)(thisPtr + 0x1024) = local_10;
  *(undefined4 *)(thisPtr + 0xf70) = DAT_00d5d934; // Some flag
  // Get weapon data
  iVar4 = FUN_00471610(); // Get weapon
  iVar4 = FUN_00471610(iVar4 + 0x10, _DAT_00d75cac); // Get weapon stats
  FUN_004a0370(thisPtr + 0xfec, iVar4 + 0x20); // Copy weapon stats
  *(undefined4 *)(thisPtr + 0xf60) = DAT_00d5d934; // Some flag
  *(undefined4 *)(thisPtr + 0xf5c) = 0; // Clear some state
  // Clear bit 0x08000000 at +0xf28 (some aiming state)
  if ((*(uint *)(thisPtr + 0xf28) >> 0x1b & 1) != 0) {
    *(uint *)(thisPtr + 0xf28) = *(uint *)(thisPtr + 0xf28) & 0xf7ffffff;
  }
  *(undefined4 *)(thisPtr + 0xf64) = 0; // Clear some timer
  FUN_008670e0(thisPtr + 0x119c, thisPtr + 0x11a0); // Set up aim animation
  FUN_0085ea10(1); // Play aim sound
  FUN_0085f170(); // Update aim state
  return result;
}