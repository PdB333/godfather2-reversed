// FUNC_NAME: debugPrintf
// Function at 0x006038a0: Wraps vsnprintf and calls the underlying log output function (0x00603610).
// Takes a format string and variable arguments, formats into a 1024-byte buffer,
// then passes it with two additional context parameters (param2, param3) and a flag (0).
// Used extensively for debug logging across the game.

#include <cstdarg>
#include <cstdio>

// Forward declaration of the actual log output function (address 0x00603610)
void logOutput(int param2, int param3, const char* message, int flag);

void debugPrintf(int param2, int param3, const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // param2 and param3 likely represent log category/severity; flag=0 indicates default behavior
    logOutput(param2, param3, buffer, 0);
}