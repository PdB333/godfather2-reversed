// FUNC_NAME: Sentient::checkPendingAction
void __thiscall Sentient::checkPendingAction(int this)
{
  // Check if current action state allows new pending action (state 0 or 0x48 = ACTION_IDLE or ACTION_READY)
  // Also check that a pending action flag (bit 12) is set and that no pending action already exists
  if ((((*(int *)(this + 0x214) == 0) || (*(int *)(this + 0x214) == 0x48)) &&
       ((*(uint *)(this + 0x1d0) >> 0xc & 1) != 0)) && (*(int *)(this + 0x290) == 0))
  {
    // Move the current action data to the pending action slot (likely copies from 0x280 to 0x290)
    // This starts a pending action from the currently prepared action buffer
    FUN_00708f80(this + 0x280, this + 0x290);
    // Clear the pending action flag
    *(uint *)(this + 0x1d0) &= 0xffffefff; // clear bit 12 (0x1000)
  }
  // Continue general update processing
  FUN_004719a0();
}