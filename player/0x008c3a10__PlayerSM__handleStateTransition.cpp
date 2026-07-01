// FUNC_NAME: PlayerSM::handleStateTransition
void __thiscall PlayerSM::handleStateTransition(int thisPtr, undefined4 param_2, int param_3, int param_4)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_00791750(); // getPlayerState() or getGameState()
  if (iVar2 < 3) {
    FUN_006b3c60(param_2); // playAnimation(param_2)
    FUN_00790110(0); // setAnimationSpeed(0)
    cVar1 = FUN_00791230(); // isAnimationFinished()
    if (cVar1 != '\0') {
      FUN_00792d80(param_2); // transitionToNextState(param_2)
      return;
    }
  }
  else {
    iVar2 = FUN_008c12a0(param_2); // getStateMachineState(param_2)
    if (iVar2 != 0) {
      if (param_4 == 2) {
        param_2 = *(undefined4 *)(thisPtr + 0x1e0); // +0x1E0: currentWeapon
        uVar3 = 3;
        if (*(int *)(thisPtr + 0x54) == 0x637b907) { // +0x54: playerClassId
          uVar3 = 1;
          param_2 = 0;
        }
        if (*(int *)(iVar2 + 4) != 7) { // +4: stateType
          FUN_008c80d0(*(undefined4 *)(param_3 + 0x38)); // playSound(param_3 + 0x38)
          FUN_008c8a20(uVar3,param_2); // spawnProjectile(uVar3, param_2)
          return;
        }
      }
      else {
        FUN_006b3c60(param_2); // playAnimation(param_2)
        FUN_008bda10(param_3,iVar2); // updateStateMachine(param_3, iVar2)
      }
    }
  }
  return;
}