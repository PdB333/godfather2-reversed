// FUNC_NAME: PlayerSM::updateState
int __fastcall PlayerSM::updateState(int thisPtr)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  
  iVar2 = *(int *)(thisPtr + 0x70); // +0x70: current state pointer
  piVar4 = *(int **)(thisPtr + 0x5c); // +0x5c: state machine vtable
  if ((iVar2 != 0) && (iVar2 = iVar2 + -0x48, iVar2 != 0)) {
    uVar3 = FUN_0043b490(); // getDeltaTime()
    FUN_007f9600(uVar3); // setDeltaTime
    FUN_007222b0(1); // enableInput
    FUN_00722370(0); // disableSomething
    FUN_0087aeb0(piVar4,0); // resetStateMachine
    FUN_007f62e0(); // updateAnimations
    FUN_007f62f0(); // updatePhysics
    FUN_0072d290(); // updateCamera
    cVar1 = (**(code **)(*piVar4 + 0x1bc))(); // checkStateTransition
    if ((cVar1 != '\0') && (iVar2 = FUN_00777310(), iVar2 == 0)) {
      FUN_0072a3e0(); // handleTransition
    }
    FUN_00777380(); // postUpdate
    *(uint *)(thisPtr + 0xac) = *(uint *)(thisPtr + 0xac) & 0xfffffff9; // clear bits 1-3
    iVar2 = thisPtr + 0x80; // +0x80: movement flags
    cVar1 = FUN_008754b0(iVar2); // isMoving
    if (cVar1 != '\0') {
      *(uint *)(thisPtr + 0xac) = *(uint *)(thisPtr + 0xac) | 2; // set bit 1 (moving flag)
    }
    cVar1 = FUN_008754e0(iVar2); // isGrounded
    if (cVar1 == '\0') {
      *(uint *)(thisPtr + 0xac) = *(uint *)(thisPtr + 0xac) | 4; // set bit 2 (airborne flag)
    }
    if (*(int *)(thisPtr + 0x70) == 0) {
      piVar4 = (int *)0x0;
    }
    else {
      piVar4 = (int *)(*(int *)(thisPtr + 0x70) + -0x48);
    }
    iVar2 = (**(code **)(*piVar4 + 0x1d8))(iVar2, thisPtr + 0x88); // updateStateMachine
    if ((*(uint *)(thisPtr + 0xac) >> 0xb & 1) == 0) {
      iVar2 = *(int *)(thisPtr + 0x70);
      if (iVar2 != 0) {
        *(int *)(iVar2 + 0xe38) = *(int *)(iVar2 + 0xe38) + 1; // increment state timer
        *(uint *)(thisPtr + 0xac) = *(uint *)(thisPtr + 0xac) | 0x800; // set bit 11 (state timer active)
        return iVar2 + -0x48;
      }
      iVar2 = 0;
      iRam00000e80 = iRam00000e80 + 1; // global state counter
      *(uint *)(thisPtr + 0xac) = *(uint *)(thisPtr + 0xac) | 0x800;
    }
  }
  return iVar2;
}