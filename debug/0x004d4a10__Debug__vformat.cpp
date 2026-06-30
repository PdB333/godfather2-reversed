// FUNC_NAME: Debug::vformat
// Address: 0x004d4a10
// Role: Custom vsnprintf wrapper that allocates a temporary buffer via alloca,
// formats the string, and if successful, outputs via a separate logging function (FUN_004d43f0).
// Returns number of characters written on success, -1 on failure.

#include <cstdio>
#include <cstdarg>
#include <cstdlib>

int __cdecl Debug::vformat(void* /* unused */, const char* format, va_list args, int bufferSize)
{
    // Allocate stack buffer for the formatted string
    char* buffer = static_cast<char*>(alloca(bufferSize));

    int written = vsnprintf(buffer, bufferSize, format, args);
    if (written >= 0 && written < bufferSize)
    {
        // Output the formatted string via the logging system
        // FUN_004d43f0 originally, assumed to be Debug::writeLog
        Debug::writeLog(buffer, written);
        return written;
    }
    return -1;
}