// FUNC_NAME: NPCDialogManager::updateDialogState
void __thiscall NPCDialogManager::updateDialogState(int thisPtr, undefined4 paramIn) {
  // +0x28: current dialog handle (0xFF = invalid)
  // +0x2c: state (1=playing, 2=waitingChoice, 3=waitingBranch? 0=idle)
  // +0x24: dialog data pointer (maybe current dialog instance)

  int state = *(int *)(thisPtr + 0x2c);
  if (state == 1) {
    int currentDialog = *(int *)(thisPtr + 0x28);
    if (currentDialog != 0xff) {
      // Release/stop the current dialog resource
      releaseDialog(currentDialog);
      *(int *)(thisPtr + 0x28) = 0xff;
    }
    // Trigger dialog start event (probably debug string)
    triggerEvent((int)&LAB_006f7670, thisPtr);
    // Reset dialog state machine
    resetDialog(thisPtr);
    *(int *)(thisPtr + 0x2c) = 0; // Transition to idle
  }
  else if ((state - 2U) < 2) {  // state == 2 or 3
    // Process player input for dialog choices
    processDialogInput(*(int *)(thisPtr + 0x24), paramIn);
    *(int *)(thisPtr + 0x2c) = 0; // Back to idle
  }
  // else: ignore (state 0 already idle)
}