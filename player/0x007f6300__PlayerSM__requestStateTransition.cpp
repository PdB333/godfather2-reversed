// FUNC_NAME: PlayerSM::requestStateTransition
void __thiscall PlayerSM::requestStateTransition(int thisPtr, char forceTransition)
{
  // Check if a transition is already in progress (bit 0 at +0x8E6)
  if (((*(byte *)(thisPtr + 0x8e6) & 1) != 0) && (forceTransition == '\0')) {
    return;
  }
  // Check if state change is already pending (bit 2 at +0x970)
  if ((*(uint *)(thisPtr + 0x970) >> 2 & 1) == 0) {
    // Mark state change as pending
    *(uint *)(thisPtr + 0x970) = *(uint *)(thisPtr + 0x970) | 4;
    // Reset state change timer/counter at +0x978
    *(undefined4 *)(thisPtr + 0x978) = 0;
  }
  // Call the actual state transition handler
  FUN_009c4ea0();
  return;
}