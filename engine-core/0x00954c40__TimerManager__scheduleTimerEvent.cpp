// FUNC_NAME: TimerManager::scheduleTimerEvent
void __thiscall TimerManager::scheduleTimerEvent(int *this, int *timerDef, int durationMs, char immediate, int userData)
{
  int globalTimerValue;
  int timerType;
  int timerSubType;
  uint currentTime;
  
  globalTimerValue = _DAT_00d5780c; // Global timer counter
  timerType = *timerDef;            // +0x00: timer type
  timerSubType = timerDef[2];       // +0x08: timer sub-type
  
  if (immediate != '\0') {
    // Immediate execution - set state to 3 (running/active)
    *this = 3;
    this[4] = timerType;            // +0x10: stored timer type
    this[5] = 0;                    // +0x14: flags
    this[6] = timerSubType;         // +0x18: stored timer sub-type
    this[7] = globalTimerValue;     // +0x1C: start time
    currentTime = FUN_00494d10();   // Get current time in ms
    this[8] = currentTime + durationMs; // +0x20: expiration time
    return;
  }
  
  if ((*this != 1) && (*this != 2)) {
    // Not already pending or active - start new timer
    *this = 1;                      // State: pending
    this[4] = timerType;
    this[5] = 0;
    this[6] = timerSubType;
    this[7] = globalTimerValue;
    currentTime = FUN_00494d10();
    this[8] = currentTime + durationMs;
    this[0x13] = userData;          // +0x4C: user data
    return;
  }
  
  // Timer already pending or active - check if we should reset
  currentTime = FUN_00494d10();
  if (currentTime < (uint)this[8]) {
    // Still within current timer window - reset timer
    *this = 1;
    this[4] = timerType;
    this[5] = 0;
    this[6] = timerSubType;
    this[7] = globalTimerValue;
    currentTime = FUN_00494d10();
    this[8] = currentTime + durationMs;
    this[0x13] = userData;
    return;
  }
  
  // Timer expired - move to active state
  *this = 2;                        // State: active
  this[0xc] = timerType;            // +0x30: active timer type
  this[0xd] = 0;                    // +0x34: active flags
  this[0xe] = timerSubType;         // +0x38: active timer sub-type
  this[0xf] = globalTimerValue;     // +0x3C: active start time
  this[0x10] = durationMs;          // +0x40: active duration
  this[0x11] = userData;            // +0x44: active user data
  return;
}