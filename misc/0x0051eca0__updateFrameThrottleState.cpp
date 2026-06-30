// FUNC_NAME: updateFrameThrottleState
// Address: 0x0051eca0
// Role: Updates a global throttle flag based on a time comparison.
//       If the previous flag was set and the current time is less than a threshold,
//       the flag remains set; otherwise it is cleared.
// Called from engine loop to control frame rate or loading throttling.

// Global state variables (addresses from data section)
extern uint8_t  g_throttleActive;   // DAT_01163cf5 (byte)
extern uint32_t g_throttleTimeLow;  // DAT_01194d08 (low 32 bits of threshold)
extern uint32_t g_throttleTimeHigh; // DAT_01194d0c (high 32 bits of threshold)

// External function returning a 64-bit timestamp or performance counter.
// Likely returns microseconds or ms since epoch.
extern uint64_t __fastcall getTimestampMs(void* context);

void __fastcall updateFrameThrottleState(void* context) // context = this pointer (ECX)
{
    // Combine two 32-bit globals into a 64-bit threshold
    uint64_t threshold = ((uint64_t)g_throttleTimeHigh << 32) | g_throttleTimeLow;

    if (g_throttleActive && (getTimestampMs(context) < threshold))
    {
        // Keep throttling active
        g_throttleActive = 1;
    }
    else
    {
        // Stop throttling
        g_throttleActive = 0;
    }
}