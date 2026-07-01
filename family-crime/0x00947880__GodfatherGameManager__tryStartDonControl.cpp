// FUNC_NAME: GodfatherGameManager::tryStartDonControl
undefined4 GodfatherGameManager::tryStartDonControl(undefined4 param_1)

{
  char cVar1;
  
  cVar1 = GodfatherGameManager::isDonControlAvailable(param_1);
  if (cVar1 != '\0') {
    GodfatherGameManager::startDonControl();
    return 1;
  }
  return 0;
}