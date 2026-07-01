// FUNC_NAME: Player::handleMissionComplete
void __fastcall Player::handleMissionComplete(int thisPtr)
{
  int *piVar1;
  int playerData;
  char isPaused;
  
  playerData = *(int *)(thisPtr + 0x58);
  if (playerData != 0) {
    isPaused = FUN_007fd720(); // IsGamePaused
    if (isPaused == '\0') {
      piVar1 = (int *)(thisPtr + 0xf0); // +0xF0: some pointer member
      *(undefined4 *)(thisPtr + 0xe4) = 8; // +0xE4: state = 8 (e.g., MISSION_COMPLETE_STATE)
      if (*piVar1 != 0) {
        FUN_004daf90(piVar1); // FreeMemory
        *piVar1 = 0;
      }
      if ((*(uint *)(playerData + 0x8e8) >> 0x15 & 1) != 0) { // +0x8E8: flags, bit 0x15 = some condition
        FUN_007f6420(0x55); // PlaySound(0x55)
        FUN_0081c830(thisPtr + 0x74); // StartMissionCompleteUI
      }
      *(undefined4 *)(thisPtr + 0x164) = *(undefined4 *)(playerData + 0x3180); // +0x164 = copy from playerData+0x3180
      FUN_0081b030(playerData, thisPtr + 0x74, 1); // SetupMissionCompleteData
      FUN_0081db00(thisPtr + 0x74); // ShowMissionCompleteUI
      FUN_007e5c10(); // UpdatePlayerStats
      FUN_007e6b70(); // UpdateMissionProgress
      return;
    }
  }
  return;
}