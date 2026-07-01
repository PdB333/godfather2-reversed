// FUNC_NAME: PlayerSM::setState
void __thiscall PlayerSM::setState(int thisPtr, undefined4 newState, char forceTransition)
{
  char oldCanTransition;
  int iVar2;
  int *vtablePtr;
  char newCanTransition;
  
  // Check if we can transition from current state based on:
  // - Current state index (this+0xd0) < 3
  // - Some state flag at this+0xb0 == 3
  // - Bit 2 (0x4) and bit 6 (0x40) of flags at this+0x5c
  if ((((*(int *)(thisPtr + 0xd0) < 3) || (*(int *)(thisPtr + 0xb0) != 3)) ||
      ((*(uint *)(thisPtr + 0x5c) >> 2 & 1) != 0)) || ((*(uint *)(thisPtr + 0x5c) >> 6 & 1) != 0)) {
    oldCanTransition = '\0';
  }
  else {
    oldCanTransition = '\x01';
  }
  
  // Store the new state
  *(undefined4 *)(thisPtr + 0xd0) = newState;
  
  // If force transition is true and we have a valid state machine at this+0x9c
  // (which is not 0x48 - likely a null/invalid sentinel)
  if (((forceTransition != '\0') && (*(int *)(thisPtr + 0x9c) != 0)) && (*(int *)(thisPtr + 0x9c) != 0x48))
  {
    // Get vtable pointer from state machine object (offset -0x48 from this+0x9c)
    if (*(int *)(thisPtr + 0x9c) == 0) {
      vtablePtr = (int *)0x0;
    }
    else {
      vtablePtr = (int *)(*(int *)(thisPtr + 0x9c) + -0x48);
    }
    // Call virtual function at vtable offset 0x1dc (likely onStateChanged or similar)
    (**(code **)(*vtablePtr + 0x1dc))(newState);
  }
  
  // Re-evaluate transition possibility with new state
  if (((*(int *)(thisPtr + 0xd0) < 3) || (*(int *)(thisPtr + 0xb0) != 3)) ||
     (((*(uint *)(thisPtr + 0x5c) >> 2 & 1) != 0 || ((*(uint *)(thisPtr + 0x5c) >> 6 & 1) != 0)))) {
    newCanTransition = '\0';
  }
  else {
    newCanTransition = '\x01';
  }
  
  // If transition capability changed, notify the state machine manager
  if (oldCanTransition != newCanTransition) {
    iVar2 = FUN_008c74d0(*(undefined4 *)(thisPtr + 200)); // Get state machine manager
    if (iVar2 != 0) {
      if (oldCanTransition != '\0') {
        FUN_008c1190(thisPtr); // Enable transitions
        return;
      }
      FUN_008c5460(thisPtr); // Disable transitions
    }
  }
  return;
}