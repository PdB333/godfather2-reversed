// FUNC_NAME: getTimeInMicroseconds
// Function address: 0x0064ab50
// Purpose: Retrieves current system time as a 64-bit value in microseconds (since Jan 1, 1601)
// Converts FILETIME (100-nanosecond intervals) to microseconds by dividing by 10.

#include <windows.h>

uint64_t getTimeInMicroseconds()
{
    _FILETIME local_8;
    GetSystemTimeAsFileTime(&local_8);

    // Combine low and high parts into a 64-bit value
    // FILETIME is in 100-ns intervals; dividing by 10 gives microseconds
    uint64_t timeInMicroseconds = local_8.dwLowDateTime | (static_cast<uint64_t>(local_8.dwHighDateTime) << 32);
    return timeInMicroseconds / 10ULL;
}