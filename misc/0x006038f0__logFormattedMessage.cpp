// FUNC_NAME: logFormattedMessage
// Address: 0x006038f0
// Role: Variadic logging function that formats a message and passes it to a log output handler.
// Uses __vsnprintf to format the string, then calls FUN_00603610 (likely LogOutput::write or similar).

#include <cstdarg>
#include <cstring>

void logFormattedMessage(void* logContext, int logLevel, const char* format, ...)
{
    char formattedBuffer[1024];          // local_1414
    // The following buffer is zeroed but appears unused in this function; may be used by the called function or for alignment.
    // char unusedBuffer[4108];          // local_1010 (0x1010 bytes)
    // int logBuffer;                    // local_1014 (unused in this scope)

    // memset(unusedBuffer, 0, sizeof(unusedBuffer)); // original code zeros this buffer
    // logBuffer = 0;

    va_list args;
    va_start(args, format);
    __vsnprintf(formattedBuffer, sizeof(formattedBuffer), format, args);
    va_end(args);

    // Call the actual log output function (FUN_00603610)
    // Parameters: pointer to log context (or log buffer), log level, formatted string, flags (0)
    FUN_00603610(logContext, logLevel, formattedBuffer, 0);
}