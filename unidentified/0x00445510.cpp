// FUN_00445510: Timer::getElapsedTime
// Returns elapsed time in seconds since last reset using QueryPerformanceCounter.
class Timer {
    // Stored timestamp from previous reset (two 32-bit halves of a LARGE_INTEGER)
    uint32_t m_lastTickLow;   // +0x00
    uint32_t m_lastTickHigh;  // +0x04

public:
    // __thiscall
    long double getElapsedTime() {
        LARGE_INTEGER currentTick;
        QueryPerformanceCounter(&currentTick);

        // Compute delta (current - stored) as signed 64-bit
        LARGE_INTEGER lastTick;
        lastTick.LowPart = m_lastTickLow;
        lastTick.HighPart = m_lastTickHigh;
        int64_t delta = currentTick.QuadPart - lastTick.QuadPart;

        // Global conversion factor: 1.0 / QueryPerformanceFrequency (seconds per tick)
        extern float g_frequencyInverse; // at 0x01163ecc
        return (long double)delta * g_frequencyInverse;
    }
};