// FUNC_NAME: TimerManager::updateTimers
void TimerManager::updateTimers(float maxElapsedTime)
{
  bool bExceededTimeBudget;
  LARGE_INTEGER currentTime;
  LARGE_INTEGER tempTime;
  int elapsedLowPart;
  uint elapsedHighPart;
  uint signMask;
  uint tempLowPart;
  uint tempHighPart;
  float elapsedSeconds;
  float fVar7;
  int *pTimer;

  QueryPerformanceCounter(&currentTime);
  EnterCriticalSection(&g_timerCriticalSection);

  // Calculate elapsed time since last call (in performance counter ticks)
  elapsedLowPart = currentTime.s.LowPart - _DAT_01205858;  // previous low part
  elapsedHighPart = (currentTime.s.HighPart - _DAT_0120585c) - (uint)(currentTime.s.LowPart < (uint)_DAT_01205858);

  // Convert to seconds, handling negative (wrapping) case
  signMask = elapsedHighPart & 0x80000000;
  // Get absolute value of elapsed time as float
  elapsedSeconds = (float)((-(float10)(longlong)(((ulonglong)signMask) << 0x20) +
                      (float10)(CONCAT44(elapsedHighPart, elapsedLowPart) & 0x7fffffffffffffff)) *
                     (float10)_DAT_01163ec8);  // frequency divisor

  // Update previous timestamp
  _DAT_01205858 = currentTime.s.LowPart;
  _DAT_0120585c = currentTime.s.HighPart;

  pTimer = g_timerList;  // linked list of active timers
  if (0x1ff < g_timerCount) {  // > 511 timers => use slow mode multiplier
    elapsedSeconds = elapsedSeconds * g_slowModeMultiplier;
  }

  while (pTimer != (int *)0x0) {
    int timerIndex = *pTimer;
    fVar7 = *(float *)(timerIndex + 0x24) - elapsedSeconds;  // decrement timer remaining time
    *(float *)(timerIndex + 0x24) = fVar7;

    // Check if timer fired (remaining < 0) and not already handled (byte at +0x1d == 0)
    if ((((!bExceededTimeBudget) && (fVar7 < 0.0)) && (*(char *)(timerIndex + 0x1d) == '\0')) || (g_forceFireAllTimers == false))
    {
      // Process expired timers
      FUN_0060ba00();  // handleTimerExpiry
      FUN_0060d1d0();  // processTimerQueue

      QueryPerformanceCounter(&tempTime);
      tempLowPart = tempTime.s.LowPart - currentTime.s.LowPart;
      tempHighPart = (tempTime.s.HighPart - currentTime.s.HighPart) - (uint)(tempTime.s.LowPart < (uint)currentTime.s.LowPart);

      uint tempSignMask = tempHighPart & 0x7fffffff;
      uint tempAbsHighPart = tempHighPart & 0x80000000;
      tempTime.s.LowPart = 0;

      // Check if elapsed processing time exceeded max allowed
      if (((float10)((-(float10)(longlong)(((ulonglong)tempHighPart & 0x80000000) << 0x20) +
           (float10)(CONCAT44(tempHighPart, tempLowPart) & 0x7fffffffffffffff)) * (float10)_DAT_01163ecc) <= (float10)maxElapsedTime))
      {
        bExceededTimeBudget = false;
      }
      else
      {
        bExceededTimeBudget = true;  // exceeded time budget, skip further timers
      }
    }

    signMask = elapsedHighPart & 0x80000000;  // keep sign mask for next iteration
    if (pTimer == (int *)0x0) {
      pTimer = (int *)0x0;
    }
    else {
      pTimer = (int *)pTimer[1];  // next timer in linked list
    }
  }

  LeaveCriticalSection(&g_timerCriticalSection);
  return;
}