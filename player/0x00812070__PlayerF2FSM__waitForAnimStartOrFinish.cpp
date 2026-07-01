// FUNC_NAME: PlayerF2FSM::waitForAnimStartOrFinish
void __thiscall FUN_00812070(void *this, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  
  // Initialize with a time value (likely animation duration or state timer)
  FUN_008115a0(param_2);
  // Set state to 3 (likely a waiting state like F2F_WAIT_ANIM)
  *(undefined4 *)((int)this + 0x50) = 3;
  // Start animation playback (param_2 may be animation ID or handle, 0xa333fe1e is a hash)
  FUN_0043aff0(param_2,0xa333fe1e);
  // Check if animation is finished
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    // Update animation state
    FUN_0043b210();
    // Check for victory condition (returns 0 if not finished, else pointer to something)
    iVar2 = FUN_0043ab70();
    if (iVar2 == 0) {
      // If not finished, get next move or animation from state machine
      iVar2 = FUN_0043b210();
      // Store the result (likely next action ID) at +0xF0
      *(undefined4 *)((int)this + 0xf0) = *(undefined4 *)(iVar2 + 8);
    }
    // Advance state machine or animation timer
    FUN_0043b1a0();
    // Re-check if animation is finished
    cVar1 = FUN_0043b120();
  }
  return;
}