// FUNC_NAME: PlayerSM::updateStateTransition
char PlayerSM::updateStateTransition(int thisPtr, undefined4 param_2, char param_3)
{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  
  cVar2 = '\0';
  if ((*(byte *)(thisPtr + 0x8e6) & 1) == 0) {
    cVar1 = FUN_007f7c50(); // likely isPlayerInCutscene
    if (cVar1 == '\0') {
      uVar4 = 0x23; // state ID for some action
    }
    else {
      uVar4 = 0x24; // state ID for cutscene
    }
    uVar4 = FUN_00798f50(uVar4); // getStateMachine
    cVar1 = FUN_0079e970(uVar4); // isStateActive
    if (cVar1 != '\0') {
      if ((*(uint *)(thisPtr + 0x2748) & 0x8000) == 0) {
        if ((*(uint *)(thisPtr + 0x2748) & 0x4000) != 0) {
          *(uint *)(thisPtr + 0x249c) = *(uint *)(thisPtr + 0x249c) & 0xdfffffff;
          cVar2 = FUN_007b9a80(thisPtr,param_2,0); // tryTransitionToState
          if (cVar2 != '\0') {
            *(uint *)(thisPtr + 0x249c) = *(uint *)(thisPtr + 0x249c) | 0x20000000;
            return cVar2;
          }
        }
      }
      else {
        *(uint *)(thisPtr + 0x24a4) = *(uint *)(thisPtr + 0x24a4) & 0xfffffff9;
        cVar2 = FUN_007b9a20(thisPtr,param_2); // tryTransitionToState
        if (cVar2 != '\0') {
          FUN_007b15c0(thisPtr,param_2); // handleStateTransition
          return cVar2;
        }
      }
    }
  }
  if ((*(uint *)(thisPtr + 0x8e4) >> 0x12 & 1) == 0) {
    if (param_3 == '\0') {
      uVar4 = FUN_00798f50(0xd); // getStateMachine for idle
      cVar1 = FUN_0079e920(uVar4); // isStateActive
    }
    else {
      uVar4 = FUN_00798f50(0xc); // getStateMachine for movement
      cVar1 = FUN_0079e970(uVar4); // isStateActive
    }
    if (cVar1 == '\0') {
      return cVar2;
    }
  }
  iVar3 = FUN_00800a90(); // isGamePaused
  if (((iVar3 == 0) || ((*(uint *)(thisPtr + 0x8e0) >> 10 & 1) == 0)) &&
     (cVar1 = FUN_007f7c50(), cVar1 == '\0')) {
    cVar2 = FUN_007b5430(thisPtr,param_2); // defaultStateTransition
    return cVar2;
  }
  return cVar2;
}