// FUNC_NAME: WriteFormattedWide
#include <stdarg.h>
#include <wchar.h>

// Wrapper around _vswprintf_p_l with null locale.
// This function takes a format string and variable arguments, and writes the formatted output into a wide character buffer.
// It is likely used throughout the EA EARS engine for safe wide string formatting.
int __fastcall WriteFormattedWide(wchar_t* dst, size_t count, const wchar_t* format, ...)
{
    int retval;
    va_list args;
    va_start(args, format);
    retval = _vswprintf_p_l(dst, count, format, nullptr, args);
    va_end(args);
    return retval;
}