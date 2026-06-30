// FUNC_NAME: PlayerActionableInfo::getCurrentActionTarget
int PlayerActionableInfo::getCurrentActionTarget(void)

{
  char cVar1;
  int iVar2;
  int this; // unaff_ESI - the unknown unaff_ESI is actually 'this' for __thiscall
  
  cVar1 = FUN_005abd70(); // probably isInCutscene() or isInputLocked()
  if (cVar1 != '\0') {
    return this + 4; // likely mCurrentActionTarget or similar at +0x04
  }
  
  cVar1 = FUN_0059c5c0(0); // definitely check some parameter, maybe isPlayerInCar()
  if (cVar1 != '\0') {
    FUN_0059c3b0(); // probably updateActionableTargets() or beginTargetSearch()
    cVar1 = FUN_005a4140(); // likely hasFoundValidTarget(), returns true if target valid
    if (cVar1 == '\0') {
      FUN_0059c3b0(); // another update or cleanup
      iVar2 = FUN_005a3f20(); // getTargetInfoObject() - returns some entity ID/pointer
      return *(int *)(iVar2 + 0xc); // return the actual target entity pointer (+0x0c in target info)
    }
  }
  
  return 0; // no target found
}