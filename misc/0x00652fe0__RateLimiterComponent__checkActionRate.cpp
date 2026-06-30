// FUNC_NAME: RateLimiterComponent::checkActionRate
// Function address: 0x00652fe0
// This function implements a rate limiter that controls how often an action can be performed.
// It uses a burst counter and a time window. Returns 1 if the action is allowed, 0 otherwise.
// When the action is blocked, it may reset the timer and increment the burst count.

int __thiscall RateLimiterComponent::checkActionRate(int this) // __thiscall, 'this' passed in EAX
{
  int currentTime = unaff_ESI; // actually some global timer, passed in ESI? or computed? We'll use currentTime variable
  uint burstInterval = *(uint *)(this + 0xb0);   // +0xB0: time window (ms) for burst
  uint burstLimit = *(uint *)(this + 0xb4);       // +0xB4: max number of actions per window
  uint flags = *(byte *)(this + 0xb8);            // +0xB8: flags (bit 2 and 3 checked)
  uint *burstCountAddr = (uint *)(this + 0x114);  // +0x114: current burst count
  int *lastResetAddr = (int *)(this + 0x118);     // +0x118: last reset time
  int *specialPtr = (int *)(this + 0x124);        // +0x124: pointer used as guard (null means active)
  int compareVal1 = *(int *)(this + 0x94);        // +0x94: some comparison value
  int compareVal2 = *(int *)(this + 0x98);        // +0x98: another comparison value (often same as +0x94)
  
  // If the special pointer is non-zero, abort (no rate limiting active?)
  if (*(int *)(this + 0x124) != 0) {
    return 0;
  }
  
  // Initialize last reset time if not set
  if (*(int *)(this + 0x118) == 0) {
    *(int *)(this + 0x118) = currentTime;
  }
  
  // Check flag bits (0x0C = bit2 and bit3 set)
  if ((flags & 0x0C) != 0) {
    // Special override when extra conditions match
    if (compareVal1 == compareVal2) {
      burstLimit = 4; // limited to 4 bursts
      // If no burst happened yet, allow a long interval
      if (*burstCountAddr == 0) {
        burstInterval = 60000; // 60 seconds
      }
    } else {
      burstInterval = 3000; // 3 seconds
    }
  }
  
  // Compute elapsed time since last reset
  uint elapsed = currentTime - *(int *)(this + 0x118);
  
  // If the time window has not expired yet, do nothing
  if (elapsed > burstInterval) {
    // Window expired, now check if we are within burst limit
    if (*burstCountAddr <= burstLimit) {
      // Within limit, allow the action (return 1)
      return 1;
    }
    // Over limit: reset the timer and increment the burst counter
    *(int *)(this + 0x118) = currentTime;
    (*burstCountAddr)++;
    // Call some function (possibly to execute the action or handle overflow)
    FUN_006539b0(); // Address: 0x6539b0, likely "handleBurstOverflow" or similar
  }
  // If window hasn't expired or we are over limit and timer reset, deny
  return 0;
}