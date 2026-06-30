// FUNC_NAME: Debug::logMessage
void Debug::logMessage(const char* format, ...)
{
    __vsnprintf(&g_debugBuffer, 0x100, format, &stack0x00000008);
    return;
}