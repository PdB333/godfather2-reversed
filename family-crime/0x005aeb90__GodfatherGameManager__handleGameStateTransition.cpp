// FUNC_NAME: GodfatherGameManager::handleGameStateTransition
void GodfatherGameManager::handleGameStateTransition(undefined4 param_1, undefined4 param_2)
{
  char cVar1;
  undefined4 in_EAX;
  undefined4 uVar2;
  undefined4 *unaff_ESI;
  
  cVar1 = FUN_0059c5c0(0); // likely isGamePaused() or isMenuActive()
  if (cVar1 == '\0') {
    cVar1 = FUN_005abd70(); // likely isPlayerAlive()
    if (cVar1 == '\0') {
      cVar1 = FUN_005a3c40(); // likely isMissionActive()
      if (cVar1 != '\0') {
        FUN_005a3a40(); // likely startMission()
        uVar2 = FUN_005ad020(param_2); // likely createMissionState(param_2)
        *unaff_ESI = uVar2;
        return;
      }
      FUN_0059bf00(); // likely returnToFreeRoam()
      return;
    }
  }
  *unaff_ESI = in_EAX;
  return;
}