// FUNC_NAME: Timer::getElapsedSeconds
// Address: 0x004d0080
// Returns elapsed seconds since the timer was last reset, using QueryPerformanceCounter.
// The timer stores the last counter value in two uint fields (low, high) at offsets 0 and 4.

#include <windows.h>

class Timer {
public:
    // Offsets: +0x00 = m_lastTimeLow (uint), +0x04 = m_lastTimeHigh (uint)
    uint m_lastTimeLow;
    uint m_lastTimeHigh;

    // Global inverse of performance counter frequency (1.0 / frequency)
    // Initialized elsewhere, e.g., from QueryPerformanceFrequency
    static float s_invFrequency; // _DAT_01163ed0

    // Returns elapsed seconds since the stored timestamp.
    float getElapsedSeconds() const {
        LARGE_INTEGER current;
        QueryPerformanceCounter(&current);

        // Compute 64-bit difference: current - stored
        uint64_t diffLow = current.LowPart - m_lastTimeLow;
        uint32_t borrow = (current.LowPart < m_lastTimeLow) ? 1 : 0;
        uint64_t diffHigh = current.HighPart - m_lastTimeHigh - borrow;

        // Combine into 64-bit signed value (absolute difference)
        // The original code uses a convoluted sign handling; we simplify to unsigned delta.
        uint64_t delta = (diffHigh << 32) | diffLow;

        // Convert to seconds using the precomputed inverse frequency
        return (float)delta * s_invFrequency;
    }
};