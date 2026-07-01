// FUNC_NAME: Player::canUseWeaponOrAbility
uint __fastcall Player::canUseWeaponOrAbility(int thisPtr)
{
  char cVar1;
  uint in_EAX;
  
  // Check if player state is 2 (likely a specific state like "in combat" or "in vehicle")
  // and if the global game state allows actions (DAT_01223394 + 0x54 is a flag)
  // and if the game is not in a specific mode (DAT_01223394 + 0x58 != 1, e.g., not in menu/cutscene)
  if (((*(int *)(thisPtr + 0x158) == 2) && (*(char *)(DAT_01223394 + 0x54) != '\0')) &&
     (*(int *)(DAT_01223394 + 0x58) != 1)) {
    // Call a function that checks if the player can perform an action (e.g., weapon/ability cooldown)
    cVar1 = FUN_0068c530(); // Likely checks cooldown or availability
    return (uint)(cVar1 == '\0'); // Returns 1 if available (cVar1 == 0), 0 otherwise
  }
  // If conditions not met, preserve the lower byte of in_EAX (likely a previous return value or flag)
  return in_EAX & 0xffffff00;
}