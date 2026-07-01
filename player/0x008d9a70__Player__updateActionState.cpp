// FUNC_NAME: Player::updateActionState
void __thiscall Player::updateActionState(int thisPtr, int param_2)
{
  int iVar1;
  int *piVar2;
  
  // Check if action is active (offset +0x190 = m_bActionActive)
  if (*(char *)(thisPtr + 0x190) != '\0') {
    FUN_008d9990(); // Likely updateActionTimer or processAction
    // Check if current action type is valid (offset +0x1b0 = m_currentActionType)
    if ((*(int *)(thisPtr + 0x1b0) != 0) && (*(int *)(thisPtr + 0x1b0) != 0x48)) {
      // Get action object pointer (offset -0x48 from action type pointer)
      if (*(int *)(thisPtr + 0x1b0) == 0) {
        piVar2 = (int *)0x0;
      }
      else {
        piVar2 = (int *)(*(int *)(thisPtr + 0x1b0) + -0x48);
      }
      // Call virtual function at vtable+0x7c (likely executeAction or updateAction)
      (**(code **)(*piVar2 + 0x7c))();
    }
    FUN_008d9640(); // Likely finalizeAction or cleanupAction
  }
  // Check pending action (offset +0x22c = m_pendingAction)
  piVar2 = (int *)(thisPtr + 0x22c);
  if (*(int *)(thisPtr + 0x22c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x22c) + -0x48;
  }
  // If pending action matches param_2, clear the pending flag and delete the action
  if ((iVar1 == param_2) &&
     (*(uint *)(thisPtr + 0x25c) = *(uint *)(thisPtr + 0x25c) & 0xfffffffe, *piVar2 != 0)) {
    FUN_004daf90(piVar2); // Likely deleteAction or releaseAction
    *piVar2 = 0;
  }
  return;
}