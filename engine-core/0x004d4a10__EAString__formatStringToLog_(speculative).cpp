// FUNC_NAME: EAString::formatStringToLog (speculative)
// Address: 0x004d4a10
// Role: Formats a string using vsnprintf into a dynamically allocated stack buffer,
//       then passes the result to an internal logging function.
// Parameters:
//   unused - (param_1) apparently unused; possibly a this pointer or logging level
//   format - printf-style format string
//   args   - va_list of arguments
//   bufferSize - size of stack buffer to allocate (via alloca)
// Returns: number of characters written on success, -1 on failure

#include <cstdarg>
#include <cstdio>
#include <malloc.h>  // for _alloca

// External logging function (address 0x004d43f0) - writes formatted string to log output
extern void processLogString(const char* formattedString);

int formatStringToLog(int /* unused */, const char* format, va_list args, size_t bufferSize) {
    // Allocate a stack buffer using alloca (matching the alloca_probe in assembly)
    char* buffer = (char*)_alloca(bufferSize);

    // Format the string into the dynamically allocated stack buffer
    int charsWritten = vsnprintf(buffer, bufferSize, format, args);

    if (charsWritten >= 0 && charsWritten < static_cast<int>(bufferSize)) {
        // Success: pass the formatted string to the engine's logging system
        processLogString(buffer);
        return charsWritten;
    }

    return -1;
}