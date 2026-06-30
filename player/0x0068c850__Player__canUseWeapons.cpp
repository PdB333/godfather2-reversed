// FUNC_NAME: Player::canUseWeapons
bool __fastcall Player::canUseWeapons(int this)
{
  char cVar1;
  
  // Check if player is alive (byte at +0x15)
  if (*(char *)(this + 0x15) == '\0') {
    return false;
  }
  
  // Check global game state pointer
  if (DAT_01129948 != 0) {
    // Check if game is paused (bit 5 of flags at +0x4c)
    if ((*(uint *)(DAT_01129948 + 0x4c) >> 5 & 1) != 0) {
      return false;
    }
    // Check if player is in a cutscene
    cVar1 = FUN_00842870(); // likely isCutscenePlaying()
    if (cVar1 != '\0') {
      return false;
    }
  }
  
  // Check if player is in a vehicle
  cVar1 = FUN_00982670(); // likely isInVehicle()
  if (cVar1 != '\0') {
    // Check if vehicle allows weapon use (byte at +0x54)
    if (*(char *)(DAT_01223394 + 0x54) == '\0') {
      return true;
    }
    // Check if player is in a combat state
    cVar1 = FUN_0068c530(); // likely isInCombatState()
    if (cVar1 != '\0') {
      // Check if player is aiming
      cVar1 = FUN_0040edb0(); // likely isAiming()
      if (cVar1 != '\0') {
        return true;
      }
      // Check if player has a weapon equipped (pointer at +0x6c)
      if (*(int *)(DAT_0112982c + 0x6c) != 0) {
        return true;
      }
    }
  }
  
  return false;
}