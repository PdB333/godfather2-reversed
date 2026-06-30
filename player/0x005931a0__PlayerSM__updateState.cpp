// FUNC_NAME: PlayerSM::updateState
void PlayerSM::updateState(void)
{
  int stateMachine;
  int iVar1;
  int iVar2;
  int iVar3;
  
  stateMachine = FUN_0056fdd0(); // Get state machine instance
  if (stateMachine == 0) {
    return;
  }
  if (*(int *)(this + 8) != 0) { // +0x8: currentState
    iVar2 = *(int *)(this + 4); // +0x4: stateData
    if ((*(uint *)(iVar2 + 4) & 0xff) < 10) { // +0x4: stateFlags (low byte = stateIndex)
      iVar3 = *(int *)(iVar2 + 0x10); // +0x10: stateValueA
    }
    else {
      iVar3 = *(int *)(iVar2 + 0x24); // +0x24: stateValueB
    }
    if (-1 < iVar3) {
      if ((*(uint *)(iVar2 + 4) & 0xff) < 10) {
        iVar2 = *(int *)(iVar2 + 0x10);
      }
      else {
        iVar2 = *(int *)(iVar2 + 0x24);
      }
      // Check bit in state mask array
      if ((*(uint *)(**(int **)(*(int *)(this + 8) + 4) + (iVar2 >> 5) * 4) &
          1 << ((byte)iVar2 & 0x1f)) != 0) {
        *(undefined1 *)(stateMachine + 0x30) = 2; // +0x30: stateResult = 2 (active)
        return;
      }
    }
  }
  *(undefined1 *)(stateMachine + 0x30) = 0; // +0x30: stateResult = 0 (inactive)
  return;
}