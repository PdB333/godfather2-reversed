// FUNC_NAME: formatTimeToString
// Function at 0x00835c80: Converts a time value in seconds to a formatted string (e.g., HH:MM:SS)
// Uses helper FUN_00835bf0 for the actual format writing.

// Struct holding decomposed time components for formatting
struct TimeComponents {
    uint seconds;   // +0x00
    uint minutes;   // +0x04
    uint hours;     // +0x08
};

char* __cdecl formatTimeToString(char* destBuffer, uint maxLenOrFlags, uint totalSeconds) {
    TimeComponents timeComp;
    uint seconds, minutes, hours;

    // Decompose total seconds into hours, minutes, seconds
    seconds = totalSeconds % 60;
    minutes = (totalSeconds / 60) % 60;
    hours   = ((totalSeconds / 60) / 60) % 24;

    // Prepare time components structure (order: seconds, minutes, hours)
    timeComp.seconds = seconds;
    timeComp.minutes = minutes;
    timeComp.hours   = hours;

    // Call formatting function: likely writes "HH:MM:SS" into destBuffer
    // destBuffer: output string
    // &timeComp: input time struct
    // maxLenOrFlags: possibly maximum buffer length or format flags
    FUN_00835bf0(destBuffer, &timeComp, maxLenOrFlags);

    return destBuffer;
}