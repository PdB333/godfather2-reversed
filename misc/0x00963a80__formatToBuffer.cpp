// FUNC_NAME: formatToBuffer

#include <cstdio>

void __cdecl formatToBuffer(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf_s(buffer, 0x100, format, args);
    va_end(args);
}