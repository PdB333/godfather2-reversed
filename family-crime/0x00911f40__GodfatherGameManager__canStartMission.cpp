// FUNC_NAME: GodfatherGameManager::canStartMission
undefined4 __thiscall GodfatherGameManager::canStartMission(int this, char param_2)

{
  char cVar1;
  
  cVar1 = FUN_0040edb0(); // likely isGamePaused or similar
  if ((((cVar1 == '\0') && (*(int *)(this + 0x5c) < 1)) && // +0x5c: missionCount or activeMissionCount
      (*(char *)(DAT_01223394 + 0x54) == '\0')) && // global flag: isCutscenePlaying or isDialogActive
     ((cVar1 = FUN_009caa70(), cVar1 == '\0' && (cVar1 = FUN_00842870(), cVar1 == '\0')))) { // likely isPlayerInVehicle, isPlayerInCombat
    if ((**(int **)(DAT_012233a0 + 4) == 0) || (**(int **)(DAT_012233a0 + 4) == 0x1f30)) { // check game state: main menu or free roam
      return 1;
    }
    cVar1 = FUN_00911c60(); // likely isMissionActive
    if (cVar1 == '\0') {
      if ((param_2 == '\0') && (cVar1 = FUN_00690150(0x30), cVar1 != '\0')) { // 0x30 = 48, maybe check for active dialog
        return 0;
      }
      cVar1 = FUN_007aeef0(); // likely isPlayerInCutscene
      if (cVar1 == '\0') {
        return 1;
      }
    }
  }
  return 0;
}