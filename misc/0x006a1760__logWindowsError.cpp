// FUNC_NAME: logWindowsError
// Function address: 0x006a1760
// Role: Retrieve last Windows error and format into a log string with a prefix.
// Uses FormatMessageA to get system error text, then combines with prefix using snprintf.
void logWindowsError(const char* prefixString)
{
    DWORD errorCode;
    HLOCAL messageBuffer;
    char formattedMessage[256];

    errorCode = GetLastError();

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        NULL
    );

    _snprintf_s(formattedMessage, sizeof(formattedMessage), _TRUNCATE, "%s %s\n", prefixString, messageBuffer);

    LocalFree(messageBuffer);
}