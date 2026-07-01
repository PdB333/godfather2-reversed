// Xbox PDB: Fesl_GameBrowserImpl_OnSubSystemConnIdle
// FUNC_NAME: Player::handleOpenWorldStateCheck
void __fastcall Player::handleOpenWorldStateCheck(int thisPtr)
{
  bool bIsValidState;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 unaff_ESI;
  char *pcVar6;
  undefined *puVar7;
  undefined4 unaff_EDI;
  undefined1 auStack_8 [4];
  undefined1 auStack_4 [4];
  
  // Check if the player's state machine is in a valid open world state
  // +0x188: pointer to state machine or state data
  // +0x10: current state index
  if ((*(int *)(thisPtr + 0x188) == 0) ||
     ((iVar3 = *(int *)(*(int *)(thisPtr + 0x188) + 0x10), 1 < iVar3 && (iVar3 < 5)))) {
    bIsValidState = true;
  }
  else {
    bIsValidState = false;
  }
  
  // Check if open world mode is enabled and we're in a valid state
  // +0x18e: open world enabled flag
  // +0x18d: some other flag (possibly "in open world")
  if (((*(char *)(thisPtr + 0x18e) != '\0') && (bIsValidState)) && (*(char *)(thisPtr + 0x18d) != '\0')) {
    // Set some state to 3 (likely "open world active")
    *(undefined4 *)(thisPtr + 400) = 3;
    
    // Get the game's debug/logging system
    piVar2 = (int *)FUN_00ad8d40(); // likely getDebugSystem()
    iVar3 = (**(code **)(*piVar2 + 0x40))(); // likely isDebugEnabled()
    if (iVar3 != 0) {
      // Get the current game mode
      iVar3 = (**(code **)(*(int *)(thisPtr + -4) + 0x50))(); // likely getGameMode()
      if (iVar3 == 1) {
        pcVar6 = "open";
      }
      else if (iVar3 == 2) {
        pcVar6 = "simple";
      }
      else if (iVar3 == 3) {
        pcVar6 = "strict";
      }
      else {
        pcVar6 = "unknown";
      }
      // Log the game mode as a debug message
      piVar2 = (int *)FUN_00ad8d40();
      piVar2 = (int *)(**(code **)(*piVar2 + 0x40))();
      (**(code **)(*piVar2 + 4))(0x48445752, 0x4e4e4154, pcVar6); // "HDWR" "TANN" (likely "TANN" = "TANN" or "TANN" = "TANN")
    }
    
    // Log the open world state
    piVar2 = (int *)FUN_00ad8d40();
    iVar3 = (**(code **)(*piVar2 + 0x40))();
    if (iVar3 != 0) {
      iVar3 = (**(code **)(*(int *)(thisPtr + -4) + 0x50))();
      puVar7 = &DAT_00e3abcc; // likely "open" string
      if (iVar3 != 1) {
        puVar7 = &DAT_00e3abd0; // likely "closed" string
      }
      piVar2 = (int *)FUN_00ad8d40();
      piVar2 = (int *)(**(code **)(*piVar2 + 0x40))();
      (**(code **)(*piVar2 + 4))(0x48445752, 0x55504e50, puVar7); // "HDWR" "NPNU" (likely "NPNU" = "NPNU" or "NPNU" = "NPNU")
    }
    
    // Get the game's time/clock system and update something
    piVar2 = (int *)(**(code **)(*DAT_0113d220 + 0x34))(); // likely getTimeManager()
    (**(code **)(*piVar2 + 0x4c))(auStack_4, auStack_8); // likely getCurrentTime()
    uVar4 = (**(code **)(*piVar2 + 0x88))(unaff_EDI, unaff_ESI); // likely getTimeOfDay()
    uVar5 = (**(code **)(*piVar2 + 0x24))(uVar4); // likely convertToSeconds()
    FUN_00b42e70(uVar5, uVar4, unaff_EDI, unaff_ESI); // likely updateOpenWorldTime()
  }
  return;
}