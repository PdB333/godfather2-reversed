// FUNC_NAME: logSystemError
// Function address: 0x006a1760
// Logs a system error message (from GetLastError) with a custom prefix.
// Uses FormatMessageA to retrieve the error string, then outputs via snprintf.

#include <windows.h>
#include <stdio.h>

void logSystemError(const char* errorPrefix)
{
    DWORD lastError = GetLastError();
    char errorBuffer[256];
    HLOCAL localBuffer = nullptr;

    // Format the system error message (allocate buffer ourselves)
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        lastError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 0x400 = default language
        (LPSTR)&localBuffer,
        0,
        nullptr
    );

    // Print prefix + error message
    _snprintf_s(errorBuffer, sizeof(errorBuffer), _TRUNCATE, "%s %s\n", errorPrefix, localBuffer);

    // Free the buffer allocated by FormatMessage
    LocalFree(localBuffer);
}