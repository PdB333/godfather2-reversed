// FUNC_NAME: PlayerSM::getActionHash
int __thiscall PlayerSM::getActionHash(void *thisPtr)
{
  int playerManager;
  bool isInCutsceneOrCover;
  int gameMode;
  int result;

  result = 0;
  // Check if player is in a cutscene or cover state
  if (thisPtr != NULL) {
    playerManager = FUN_0043b870(*(int*)0x0113105c); // DAT_0113105c -> gPlayerManager
    if (playerManager != 0) {
      // Bit 2 of byte at +0x78 indicates cutscene
      isInCutsceneOrCover = ((*(byte*)(playerManager + 0x78) >> 2) & 1) != 0 &&
                             FUN_009b3280() != 0; // isInCover()?
      if (isInCutsceneOrCover) {
        return 0x9b1fb963; // cutscene/cover action hash
      }
    }
  }

  // Check bit 1 of uint at +0x8e0 (likely a combat/action flag)
  if ((*(uint*)((int)thisPtr + 0x8e0) >> 1 & 1) == 0) {
    // Normal mode: get game mode (0=exploration,1=combat,2-4=others)
    gameMode = FUN_00800b60(); // getGameMode()
    switch(gameMode) {
    case 0:
      result = 0x389804ab; // idle action
      if ((*(uint*)((int)thisPtr + 0x1f5c) >> 0x12 & 1) != 0) {
        return 0xb96976be; // special action (maybe sprint/shoot)
      }
      break;
    case 1:
      return 0x389804ab; // combat idle
    case 2:
    case 3:
    case 4:
      result = 0x4cc1eb71; // other action (e.g., driving)
    }
  } else {
    // Alternative mode (e.g., cover/combat stance)
    gameMode = FUN_00800b60(); // getGameMode()
    switch(gameMode) {
    case 0:
    case 1:
      return 0x52e7d170; // cover idle
    case 2:
    case 3:
    case 4:
      return 0x84343fc4; // cover other
    }
  }
  return result;
}