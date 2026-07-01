// FUNC_NAME: Debug::outputFormattedLogString
// Address: 0x008f22f0
// This function formats a log string with a "GF2-" prefix and a timestamp/ID,
// then outputs it via a debug log system.

#include <cstdint>

// External function to get a string representation of current time or an identifier.
// 0xFFFFFFFF might indicate "current" or "default" source.
extern const char* getTimestampString(uint32_t sourceId);

// External function to format a string into a buffer (like sprintf) and possibly store it.
// param1 is likely a buffer or context pointer.
extern void formatLogString(void* buffer, const char* format, ...);

// External function to flush or actually output the formatted log.
extern void flushLogOutput();

void Debug::outputFormattedLogString(void* logContext)
{
    const char* timestamp = getTimestampString(0xFFFFFFFF);
    formatLogString(logContext, "GF2-%s-", timestamp);
    flushLogOutput();
}