// FUNC_NAME: eaDebugPrintf
// Address: 0x006038a0
// This function formats a debug string using a variable argument list and passes it to the logging output routine.
// It is called from numerous locations across the game for debug output (likely EARS engine logging).
// The actual output target is FUN_00603610 (presumably Log::outputLine or similar).

void eaDebugPrintf(uint32 logLevel, uint32 channel, const char* format, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, format);
    __vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Forward the formatted message to the lower-level logging function.
    // The final parameter (0) might be a flag or severity modifier.
    FUN_00603610(logLevel, channel, buffer, 0);
}