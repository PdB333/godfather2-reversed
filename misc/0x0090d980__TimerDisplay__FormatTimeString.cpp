// FUNC_NAME: TimerDisplay::FormatTimeString
// Function address: 0x0090d980
// Role: Formats a timer value from internal state into a minutes:seconds string buffer.
// The object has a flags field (bit2 indicates countdown vs elapsed mode), two time fields,
// and a formatted string buffer at offset 8 (which overlaps with time2).
// If bit2 of flags is clear, uses (time2 - time1) as milliseconds; if set, uses time1 directly.
// Converts milliseconds to seconds (rounding to nearest), then to minutes and seconds,
// and writes the result into the buffer at offset 8 via FormatMinutesSeconds().

#include <cstdint>

// Forward declaration: writes formatted minutes:seconds into a char buffer.
// (Located at 0x006042f0)
extern void FormatMinutesSeconds(int minutes, int seconds, char* buffer);

class TimerDisplay {
public:
    // +0x00
    uint32_t flags;      // Bit2: 0 = countdown (difference), 1 = elapsed (use time1)
    // +0x04
    uint32_t time1;      // Start time (or elapsed time in elapsed mode)
    // +0x08
    uint32_t time2;      // End time (countdown mode) / also start of formatted string buffer

    void FormatTimeString() {
        uint32_t msDuration;

        if ((flags >> 2) & 1) {
            // Elapsed mode: use time1 directly (milliseconds)
            msDuration = time1;
        } else {
            // Countdown mode: remaining time = time2 - time1 (milliseconds)
            msDuration = time2 - time1;
        }

        // Round milliseconds to nearest second
        uint32_t seconds = (msDuration + 500) / 1000;

        // Write "MM:SS" into the buffer starting at &time2
        FormatMinutesSeconds(seconds / 60, seconds % 60, reinterpret_cast<char*>(&time2));
    }
};