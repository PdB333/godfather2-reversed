// FUNC_NAME: PlayerActionableInfo::canPerformAction
undefined4 __fastcall PlayerActionableInfo::canPerformAction(int thisPtr)

{
  int gameManager;
  char isSprinting;
  
  gameManager = *(int *)(thisPtr + 0x58);  // +0x58: game manager pointer
  // Check if not performing a tall action (bit 2 of 0x8e8) and not sprinting (bit 9 of 0x8e0)
  if (((*(uint *)(gameManager + 0x8e8) >> 2 & 1) == 0) && ((*(uint *)(gameManager + 0x8e0) >> 9 & 1) == 0)) {
    return 1;
  }
  // Check if the player is in a state that allows action override (e.g., from cover)
  isSprinting = FUN_007d0060(gameManager);  // likely checkIfInOverrideState
  if ((((isSprinting != '\0') && (gameManager = *(int *)(thisPtr + 0x58), *(int *)(gameManager + 0x24f8) != 0)) &&
      ((*(uint *)(gameManager + 0x8e0) >> 9 & 1) == 0)) && ((*(uint *)(gameManager + 0x249c) >> 0x17 & 1) == 0))
  {
    // Check if we can afford/make room for another action (0x40 = 64, likely a cooldown or action limit)
    isSprinting = FUN_00690150(0x40);  // likely checkActionAvailability
    if (isSprinting == '\0') {
      return 1;
    }
  }
  return 0;
}