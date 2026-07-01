// FUNC_NAME: DebugLogger::logWithTimestamp

// Address: 0x007b9be0
// Role: Prepends a 12-byte timestamp (from a global source) to a formatted log message.
// The timestamp is obtained as three consecutive DWORDs from a static pointer, then passed
// along with five user-supplied DWORDs to an underlying logging function.

void DebugLogger::logWithTimestamp(
    uint32_t arg1,
    uint32_t arg2,
    uint32_t arg3,
    uint32_t arg4,
    uint32_t arg5)
{
    // Retrieve pointer to global timestamp data (3 DWORDs, e.g., seconds, microseconds, ticks)
    uint32_t* timeData = (uint32_t*)FUN_00555290();

    // Copy timestamp components into local variables
    uint32_t timePart1 = timeData[0];
    uint32_t timePart2 = timeData[1];
    uint32_t timePart3 = timeData[2];

    // Call the actual logging function with timestamp and user arguments.
    // The three trailing zeroes likely represent optional flags or additional parameters.
    FUN_0054ebf0(&timePart1, arg1, arg2, arg3, arg4, arg5, 0, 0, 0);
}