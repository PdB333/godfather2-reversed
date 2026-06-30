// FUNC_NAME: Sentient::updateStateMachine
void __thiscall Sentient::updateStateMachine(int thisPtr)
{
  // +0x34: flags (bit 11 = flag0, bit 25 = flag1, bit 18 = flag2, bit 19 = flag3)
  // +0x16c: some status flag (e.g., isDead, isActive)
  // +0xd4: pointer to some target/state object (e.g., currentGoal)

  int *flags = (int *)(thisPtr + 0x34);
  int statePtr = *(int *)(thisPtr + 0xd4);

  // Check if bit 11 of flags is clear
  if (((*flags >> 0xb) & 1) == 0)
  {
    // Set bit 25
    *flags = *flags | 0x2000000;

    // If the entity is in a certain inactive state (e.g., dead or disabled)
    if (*(int *)(thisPtr + 0x16c) == 0)
    {
      if (statePtr != 0)
      {
        // Set bit 18 and dispatch an event with the global data
        *flags = *flags | 0x40000;
        dispatchEvent(PTR_LAB_00d5dbb0, DAT_0112a650, 0, thisPtr);
        return;
      }

      // No target: set bit 19 and call idle state handler
      *flags = *flags | 0x80000;
      setIdleState(1, 0);
    }
  }
}