// FUNC_NAME: pushDebugValue

void pushDebugValue(uint32_t value)
{
    // Global debug buffer array at 0x011946b8 and index at 0x011946b4
    g_debugBuffer[g_debugBufferIndex] = value;
    g_debugBufferIndex++;
}