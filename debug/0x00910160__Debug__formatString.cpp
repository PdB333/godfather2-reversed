// FUNC_NAME: Debug::formatString
void Debug::formatString(char *outBuffer, const char *format, ...)
{
    // Wrapper around vsprintf_s with a fixed buffer size of 0x40 (64 bytes)
    // Used for formatting debug strings throughout the game
    _vsprintf_s(outBuffer, 0x40, format, (va_list)&format + 1);
}