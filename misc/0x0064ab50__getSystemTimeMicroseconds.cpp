// FUNC_NAME: getSystemTimeMicroseconds
#include <windows.h>

// Returns the current system time in microseconds since January 1, 1601.
// Uses GetSystemTimeAsFileTime (100-ns intervals) and divides by 10 to get microseconds.
uint64_t getSystemTimeMicroseconds()
{
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime);

    // Combine low and high parts into a 64-bit value (100-ns intervals)
    uint64_t time100ns = ((uint64_t)fileTime.dwHighDateTime << 32) | fileTime.dwLowDateTime;

    // Convert to microseconds (100 ns / 10 = 10 µs? Actually 100 ns = 0.1 µs, so dividing by 10 gives µs)
    return time100ns / 10ull;
}