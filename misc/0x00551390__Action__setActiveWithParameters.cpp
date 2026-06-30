// FUNC_NAME: Action::setActiveWithParameters
void __thiscall Action::setActiveWithParameters(bool active, int duration, int startTime)
{
  if (active) {
    // Clear the "disabled" flag (bit 1) to indicate active
    *(uint *)(this + 0xe4) &= ~2U;
    *(int *)(this + 0xb8) = startTime;   // +0xb8: start time or remaining time
    *(int *)(this + 0xb4) = duration;    // +0xb4: duration or total time
  } else {
    // Set the "disabled" flag (bit 1)
    *(uint *)(this + 0xe4) |= 2;
    *(int *)(this + 0xb8) = 1;           // Reset to minimal value
    *(int *)(this + 0xb4) = 0;           // Zero duration
  }
}