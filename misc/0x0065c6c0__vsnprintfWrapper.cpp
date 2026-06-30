// FUNC_NAME: vsnprintfWrapper
// Address: 0x0065c6c0
// Role: Internal vsnprintf wrapper that takes an unused first parameter (likely log level or module ID) and passes through to _vsnprintf with a va_list. Used as backend for logging/string formatting functions.

#include <cstdarg>
#include <cstdio> // or stdio.h for __vsnprintf

void __fastcall vsnprintfWrapper(int /*ignored*/, size_t count, char* buffer, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    __vsnprintf(buffer, count, format, args);
    va_end(args);
}