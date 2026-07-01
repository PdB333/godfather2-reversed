// FUNC_NAME: Player::handleEnterExitTrigger
undefined4 __fastcall Player::handleEnterExitTrigger(int this)

{
  char cVar1;
  
  cVar1 = isPlayerEnteringExit();  // checks if player is near/triggering an enter/exit
  if (cVar1 != '\0') {
    setPlayerExitState(1);  // enter exit state
    exitTransitionTime = 0x24;  // +0x94 time to play transition anim
    *(undefined4 *)(this + 0x60) = 0;  // +0x60 clear some state flag
    if ((guardFlag & 1) == 0) {
      initEnterExitCleanup(this + 0x14,&LAB_00931e00,0);  // setup timer/callback for cleanup
      guardFlag = guardFlag | 1;
    }
    return 1;
  }
  return 0;
}