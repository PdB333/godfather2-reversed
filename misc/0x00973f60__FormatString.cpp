// FUNC_NAME: FormatString
void FormatString(char *outputBuffer, const char *format, ...)
{
    // Secure formatted output with a maximum buffer size of 100 characters.
    // Uses the va_list passed from the variadic arguments.
    va_list args;
    va_start(args, format);
    _vsprintf_s(outputBuffer, 100, format, args);
    va_end(args);
}