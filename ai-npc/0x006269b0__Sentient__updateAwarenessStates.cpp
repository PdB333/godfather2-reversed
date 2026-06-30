// FUNC_NAME: Sentient::updateAwarenessStates
void Sentient::updateAwarenessStates(void)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  int this; // unaff_EDI - pointer to Sentient object
  
  // Check if 'awarenessDisabled' flag is set (at +0x6)
  if (*(char *)(this + 6) == '\0') {
    // Check if 'visualSensed' state (at +0x14) has a timer that hasn't expired
    // +0x14 = pointer to an awareness state object
    // +5 = disabled/expired flag? &0x11 checks if either bit 0 or 4 is set
    if ((*(byte *)(*(int *)(this + 0x14) + 5) & 0x11) == 0) {
      FUN_00626640(); // likely disableAwarenessState or resetTimer
    }
    // Check if 'audioSensed' state (at +0xc) similarly
    if ((*(byte *)(*(int *)(this + 0xc) + 5) & 0x11) == 0) {
      FUN_00626640();
    }
    iVar3 = 0;
    // Check 'awarenessStateCount' (at +0x7) - number of special awareness states
    if (*(char *)(this + 7) != '\0') {
      piVar2 = (int *)(this + 0x18); // start of special awareness state array
      do {
        iVar1 = *piVar2; // pointer to a state object
        // Check if state is not disabled (at +0x5)
        if (*(char *)(iVar1 + 5) == '\0') {
          // If state's 'priority' (at +0xc) is > 3 and its 'timer' (at +0x10) is not expired
          if ((3 < *(int *)(iVar1 + 0xc)) && ((*(byte *)(*(int *)(iVar1 + 0x10) + 5) & 0x11) == 0))
          {
            FUN_00626640(); // disable or expire the state
          }
          // Mark state as disabled/expired
          *(undefined1 *)(iVar1 + 5) = 1;
        }
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar3 < (int)(uint)*(byte *)(this + 7));
    }
  }
  else {
    // If 'awarenessDisabled' is set, clear all states
    iVar3 = 0;
    if (*(char *)(this + 7) != '\0') {
      piVar2 = (int *)(this + 0x14); // start of alternate layout? (pointer + adjacent count)
      do {
        // piVar2[-1] = count of a certain type? 3 is a threshold
        if ((3 < piVar2[-1]) && ((*(byte *)(*piVar2 + 5) & 0x11) == 0)) {
          FUN_00626640();
        }
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 2; // skipping 8 bytes per entry (pointer + count?)
      } while (iVar3 < (int)(uint)*(byte *)(this + 7));
      return;
    }
  }
  return;
}