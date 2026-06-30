// FUNC_NAME: formatString
void __fastcall formatString(char *buffer, size_t size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    __vsnprintf(buffer, size, format, args);
    va_end(args);
}