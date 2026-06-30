// FUNC_NAME: vsnprintfSafe
void vsnprintfSafe(char* outBuf, int outBufSize, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    __vsnprintf(outBuf, outBufSize - 1, fmt, args);
    va_end(args);
    outBuf[outBufSize - 1] = '\0'; // ensure null termination
}