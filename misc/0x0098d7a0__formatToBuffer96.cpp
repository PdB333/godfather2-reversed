// FUNC_NAME: formatToBuffer96
void formatToBuffer96(char* dest, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    _vsprintf_s(dest, 0x60, format, args);
    va_end(args);
}