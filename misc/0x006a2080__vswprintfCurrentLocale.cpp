// FUNC_NAME: vswprintfCurrentLocale
void __fastcall vswprintfCurrentLocale(wchar_t *buffer, size_t bufferCount, const wchar_t *format, ...)
{
    // Wrapper for _vswprintf_p_l with NULL locale (current locale)
    // buffer: destination buffer
    // bufferCount: maximum number of characters to write (including null terminator)
    // format: format string
    // ...: variable arguments
    va_list args;
    va_start(args, format);
    _vswprintf_p_l(buffer, bufferCount, format, nullptr, args);
    va_end(args);
}