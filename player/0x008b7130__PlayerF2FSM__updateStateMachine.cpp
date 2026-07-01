// FUNC_NAME: PlayerF2FSM::updateStateMachine
void __thiscall PlayerF2FSM::updateStateMachine(int param_1, int param_2)
{
  uint flags;
  char subComponentActive;
  int globalState;

  globalState = FUN_006b4860();
  flags = *(uint *)(param_1 + 0x290); // +0x290: bitfield of state flags
  if ((flags & 0x10) == 0) {
    if ((flags & 0x20) == 0) {
      if (globalState != 0) goto LAB_008b7220;
      // Check if we should enter aiming/combat state
      if ((((char)flags < '\0') && (*(int *)(param_2 + 0x40) == 0x637b907)) ||
         (((flags & 0x40) != 0 && (subComponentActive = FUN_008b7de0(param_1 + 0x20), subComponentActive != '\0'))))
        goto LAB_008b7261;
      // Transition to idle/stop aiming
      FUN_008b92d0(); // stopAiming
      FUN_008b70d0(); // stopMoving
    }
    else {
      if (globalState == 0) {
        if (((char)flags >= '\0') || (*(int *)(param_2 + 0x40) != 0x637b907)) {
          subComponentActive = FUN_008b7de0(param_1 + 0x20); // check subcomponent state
          if (subComponentActive == '\0') {
            FUN_008b92d0(); // stopAiming
            FUN_008b70d0(); // stopMoving
            FUN_008b7dc0(param_1 + 0x20); // disable subcomponent
            return;
          }
        }
LAB_008b7261:
        // Enter aiming/combat state
        FUN_008b9250(); // startAiming
        FUN_008b7100(); // startMoving
        return;
      }
      // globalState != 0
      FUN_008b92d0(); // stopAiming
      globalState = FUN_0043b870(DAT_0112af98); // get global manager pointer
      if ((~*(byte *)(globalState + 0x50) & 1) != 0) { // check some permission flag
        FUN_007894b0(); // maybe release control
        FUN_008b7dc0(param_1 + 0x20); // disable subcomponent
        return;
      }
    }
    FUN_008b7dc0(param_1 + 0x20); // ensure subcomponent disabled
  }
  else {
    // flags & 0x10 set
    if (globalState == 0) {
      if (((*(uint *)(param_2 + 0x34) >> 0x12 & 1) == 0) && // check bit 18 of target flags
         ((*(uint *)(param_2 + 0x34) >> 0x1c & 1) == 0)) { // check bit 28
        FUN_008b92d0(); // stopAiming
        FUN_008b70d0(); // stopMoving
        return;
      }
    }
    else if ((globalState == 4) || (globalState == 3)) {
      FUN_008b9250(); // startAiming
    }
LAB_008b7220:
    globalState = FUN_0043b870(DAT_0112af98);
    if ((~*(byte *)(globalState + 0x50) & 1) != 0) {
      FUN_007894b0(); // release control
      return;
    }
  }
  return;
}