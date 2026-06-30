// FUNC_NAME: TimeManager::updateElapsedTime
void TimeManager::updateElapsedTime(void)
{
  LARGE_INTEGER currentTime;
  
  QueryPerformanceCounter(&currentTime);
  
  // Check if current time is >= last recorded time (no wrap-around)
  if ((DAT_01194b7c <= (uint)currentTime.s.HighPart) &&
     ((DAT_01194b7c < (uint)currentTime.s.HighPart || (DAT_01194b78 < currentTime.s.LowPart)))) {
    // Normal case: current time is after last time
    // Compute elapsed time as difference (low part)
    DAT_01194b70 = currentTime.s.LowPart - DAT_01194b78;
    // Compute elapsed time as difference (high part with borrow)
    DAT_01194b74 = (currentTime.s.HighPart - DAT_01194b7c) - (uint)(currentTime.s.LowPart < DAT_01194b78);
    return;
  }
  
  // Wrap-around case: current time is before last time (counter wrapped)
  // Compute elapsed time as two's complement of the negative difference
  DAT_01194b70 = ~(DAT_01194b78 - currentTime.s.LowPart) + 1;
  DAT_01194b74 = ~((DAT_01194b7c - currentTime.s.HighPart) - (uint)(DAT_01194b78 < currentTime.s.LowPart)) +
                 (uint)(0xfffffffe < ~(DAT_01194b78 - currentTime.s.LowPart));
  return;
}