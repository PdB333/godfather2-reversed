// FUNC_NAME: Player::canEnterVehicle
undefined4 __fastcall Player::canEnterVehicle(int this)
{
  uint flags;
  char isPressed;
  int gameState;

  if ((DAT_0112a838 == 0) || (*(int *)(DAT_0112a838 + 0x5c) == 0)) {
    gameState = FUN_007abe90(); // likely getGameState or isGameActive
    if (gameState == 0) {
      return 0;
    }
    // Check if player is alive (bit 0 of health/state flags at +0x4)
    if (((*(byte *)(*(int *)(this + 0x74) + 4) & 1) != 0) &&
       (gameState = FUN_007ab160(), (*(byte *)(gameState + 4) & 4) != 0)) {
      flags = *(uint *)(*(int *)(this + 0x58) + 0x8e0); // +0x8e0: player action flags
      if ((flags & 0x1000000) == 0) { // not in some restricted state
        return 1;
      }
      // Check if specific action keys are pressed (enter vehicle key 0x42 = 'B', or 9 = Tab)
      if (((flags >> 0x19 & 1) != 0) &&
         ((isPressed = FUN_007aefe0(0x42), isPressed != '\0' || 
           (isPressed = FUN_007aefe0(9), isPressed != '\0'))))
      {
        return 1;
      }
    }
  }
  return 0;
}