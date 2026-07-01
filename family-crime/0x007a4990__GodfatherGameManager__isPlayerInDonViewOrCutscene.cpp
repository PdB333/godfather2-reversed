// FUNC_NAME: GodfatherGameManager::isPlayerInDonViewOrCutscene
undefined1 __thiscall GodfatherGameManager::isPlayerInDonViewOrCutscene(undefined4 this, int param_2)

{
  char cVar1;
  
  cVar1 = FUN_00481660(); // likely GodfatherGameManager::isInDonView()
  if ((((cVar1 != '\0') || (cVar1 = FUN_00481640(), cVar1 != '\0')) && (param_2 != 0)) &&
     (cVar1 = FUN_007a4900(this), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}