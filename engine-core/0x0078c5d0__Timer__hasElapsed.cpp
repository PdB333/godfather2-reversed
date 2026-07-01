// FUNC_NAME: Timer::hasElapsed
bool __thiscall Timer::hasElapsed(int thisPtr, byte flagIndex)
{
  // +0x1c: elapsed time (float)
  // +0x20: flags bitmask (byte)
  // DAT_01205228: some global threshold value (likely max time or a sentinel)
  
  if (*(float *)(thisPtr + 0x1c) <= DAT_01205228 && DAT_01205228 != *(float *)(thisPtr + 0x1c)) {
    // If elapsed time hasn't exceeded threshold and threshold isn't equal to elapsed time,
    // reset the timer: clear flags and set elapsed time to 0
    *(byte *)(thisPtr + 0x20) = 0;
    *(float *)(thisPtr + 0x1c) = 0.0f;
  }
  
  // Check if the specific flag bit is set (using bit shift with mask to handle byte boundaries)
  return (1 << (flagIndex & 0x1f) & *(byte *)(thisPtr + 0x20)) != 0;
}