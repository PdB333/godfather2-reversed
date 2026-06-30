// FUNC_NAME: TimeRange::isActive
// Address: 0x006b2ed0
// Checks if the current game time falls within an active interval defined by two float members (m_fStartTime at +0x104, m_fEndTime at +0x108).
// Handles wrap-around intervals (e.g., 22:00 to 06:00) correctly. Returns true if a global timer system is disabled or if start == end.

bool __thiscall TimeRange::isActive(void *this)
{
    float startTime = *(float *)((char *)this + 0x104);   // +0x104: m_fStartTime
    float endTime   = *(float *)((char *)this + 0x108);   // +0x108: m_fEndTime
    // global flag to disable time-based events (checked by the game)
    extern bool g_gameTimersEnabled;                      // DAT_0112a53c

    // If the timer system is disabled or the interval is zero-length, always active.
    if (startTime == endTime || !g_gameTimersEnabled) {
        return true;
    }

    // Get current game time components (e.g., hours, minutes, seconds)
    // Function FUN_00826540 likely fills a 12-byte buffer with three floats.
    float timeComponents[3];
    getGameTimeComponents(timeComponents);

    // Combine components into a single float representing the current time in the same unit
    // as start/end. The globals are conversion factors (e.g., seconds to hours, minutes to hours).
    extern float g_secondsFactor;  // _DAT_00d5e28c
    extern float g_minutesFactor;  // DAT_00e446b4
    float currentTime = timeComponents[0] * g_secondsFactor + timeComponents[1] * g_minutesFactor + timeComponents[2];

    // Determine if currentTime lies within the active interval.
    // If endTime < startTime, the interval wraps (e.g., night hours).
    if (endTime < startTime) {
        // Wrapped case: active when time >= startTime OR time <= endTime
        if (currentTime >= startTime || currentTime <= endTime) {
            return true;
        }
    } else {
        // Normal case: active when time is between startTime and endTime inclusive
        if (currentTime >= startTime && currentTime <= endTime) {
            return true;
        }
    }
    return false;
}