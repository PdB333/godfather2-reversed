// FUNC_NAME: safeVswprintf
// Address: 0x006a3680
// Role: Thin wrapper around _vswprintf_p_l for safe wide string formatting with varargs.
// Parameters: dest (output buffer), destSize (buffer size in characters), format (printf-style format string), ...
void __fastcall safeVswprintf(wchar_t *dest, size_t destSize, const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);
    _vswprintf_p_l(dest, destSize, format, nullptr, args);
    va_end(args);
}