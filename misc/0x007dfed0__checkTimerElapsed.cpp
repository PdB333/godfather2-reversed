// FUNC_NAME: checkTimerElapsed

bool checkTimerElapsed(int startTime, float timeMultiplier)
{
    // Get current time from a timer function (likely milliseconds or ticks)
    int currentTime = getCurrentTime(); // FUN_007ab290
    
    // Calculate elapsed time as float, handling 32-bit timer overflow wrap
    float elapsed = (float)(startTime - currentTime);
    if (startTime - currentTime < 0) {
        // Wrap around: add the maximum timer value (2^32 as float)
        elapsed += (float)TIMER_WRAP_CONSTANT; // DAT_00e44578 = 4294967296.0f
    }
    
    // Compute allowed time: multiplier * base time unit (e.g., 1000.0 for seconds->ms)
    float allowedTime = timeMultiplier * TIME_BASE_CONSTANT; // DAT_00d60d04 = 1000.0f
    
    // Return true if elapsed time meets or exceeds the limit
    return (allowedTime <= elapsed);
}