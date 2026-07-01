// FUNC_NAME: GodfatherGameManager::attemptMissionStart
int GodfatherGameManager::attemptMissionStart(void)

{
  int iVar1;
  
  GodfatherGameManager::checkCurrentMissionState();
  iVar1 = GodfatherGameManager::isMissionActive();
  if (iVar1 != 0) {
    GodfatherGameManager::launchMissionBegin();
    return 1;
  }
  return 0;
}