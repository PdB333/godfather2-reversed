// FUNC_NAME: vsprintf_s_wrapper
void vsprintf_s_wrapper(char *buffer, char *format, ...)
{
    _vsprintf_s(buffer, 4, format, &stack0x0000000c);
    return;
}