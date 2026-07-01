// FUNC_NAME: GodfatherGameManager::updateMainLoop
void __fastcall GodfatherGameManager::updateMainLoop(GodfatherGameManager* this)
{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = DAT_01223484; // g_pPlayer pointer
  if (DAT_01223484 != 0) {
    *(uint *)(DAT_01223484 + 0x37c) = *(uint *)(DAT_01223484 + 0x37c) & 0xfffffdff; // Clear bit 9 of player flags
  }
  FUN_00566f00(*(undefined4 *)(this + 0x134), this + 0x138); // Update some timer/cooldown
  if (((iVar1 != 0) && (*(int *)(iVar1 + 0x28) != 0 || *(int *)(iVar1 + 0x2c) != 0)) &&
     (iVar1 != -0x28)) {
    if (0xf < *(byte *)(DAT_01129814 + 0x14)) { // Check some global counter
      FUN_0068cbc0(*(undefined1 *)(this + 0x134)); // Call some function with parameter
    }
    iVar1 = DAT_0112980c; // g_pGameStateManager
    uVar3 = FUN_00683280("FrontendMainLoop"); // Get string hash
    iVar4 = FUN_006833d0(uVar3); // Get current game state
    if (iVar4 == *(int *)(iVar1 + 4)) { // Check if in frontend state
      if (DAT_01129930 != 0) { // g_bShowFrontend
        cVar2 = FUN_008a4380(); // Check if frontend is active
        if (cVar2 != '\0') {
          cVar2 = FUN_00963fd0(); // Check some condition
          if (cVar2 != '\0') {
            FUN_009718a0(); // Update frontend
          }
        }
      }
      if (DAT_01129928 != 0) { // g_bShowMenu
        FUN_00936790(); // Update menu
        return;
      }
    }
    else {
      uVar3 = FUN_00683280("GameMainLoop"); // Get string hash
      iVar4 = FUN_006833d0(uVar3); // Get current game state
      if (iVar4 == *(int *)(iVar1 + 4)) { // Check if in game state
        if ((DAT_011298a0 == 0) || (*(char *)(DAT_011298a0 + 0x2c) == '\0')) { // Check if game is paused
          DAT_00e5672c = 0x19; // Set some global timer
          FUN_0067c920(); // Update game logic
          return;
        }
        FUN_009bca50(); // Handle pause
        *(undefined1 *)(this + 0x140) = 1; // Set pause flag
      }
    }
  }
  return;
}