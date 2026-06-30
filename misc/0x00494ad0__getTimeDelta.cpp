// FUNC_NAME: getTimeDelta
// Function at 0x00494ad0: Reads current high-resolution timer, stores it in a global structure, and returns the delta since the last recorded time.
// The global structure at gTimerData (0x0110a580) has two 64-bit timestamps: m_oldTime (offsets 0-7) and m_newTime (offsets 8-15).
// This function updates m_newTime with the current timer value, then returns (m_newTime - m_oldTime) as a signed 64-bit difference.
// The caller is expected to later copy m_newTime to m_oldTime (or this function is part of a pair).

#include <cstdint>

// Global pointer to timer data structure (resolved from PTR_DAT_0110a580)
extern volatile uint8_t* gTimerData; // Actually a pointer to a struct

// Forward declaration of low-level timer function (returns 64-bit timestamp)
extern "C" uint64_t __cdecl getRawTimer(void); // from FUN_00402270

// Structure representing the timer data at gTimerData
struct TimerData {
    int32_t m_oldTimeLow;   // +0x00
    int32_t m_oldTimeHigh;  // +0x04
    int32_t m_newTimeLow;   // +0x08
    int32_t m_newTimeHigh;  // +0x0C
};

// Reconstructed function
int64_t __cdecl getTimeDelta(void) {
    TimerData* timer = reinterpret_cast<TimerData*>(gTimerData);

    // Get current raw timer (64-bit value)
    uint64_t rawTime = getRawTimer();

    // Store new time in structure (offsets 0x08-0x0F)
    timer->m_newTimeLow  = static_cast<int32_t>(rawTime);
    timer->m_newTimeHigh = static_cast<int32_t>(rawTime >> 32);

    // Compute 64-bit delta: newTime - oldTime
    int32_t oldLow  = timer->m_oldTimeLow;
    int32_t oldHigh = timer->m_oldTimeHigh;
    int32_t newLow  = timer->m_newTimeLow;
    int32_t newHigh = timer->m_newTimeHigh;

    // Perform 64-bit subtraction with borrow
    uint32_t lowDiff = static_cast<uint32_t>(newLow) - static_cast<uint32_t>(oldLow);
    uint32_t borrow  = (static_cast<uint32_t>(newLow) < static_cast<uint32_t>(oldLow)) ? 1 : 0;
    int32_t highDiff = newHigh - oldHigh - borrow;

    // Combine into signed 64-bit result
    return (static_cast<int64_t>(highDiff) << 32) | static_cast<uint64_t>(lowDiff);
}