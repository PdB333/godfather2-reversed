// FUNC_NAME: debugLogPrintf
// Address: 0x006038f0
// Role: Variadic debug log function that formats a string using vsnprintf and forwards to the internal logging system.
void __cdecl debugLogPrintf(int logContext, uint32_t flags, const char* format, ...)
{
    char formattedBuffer[1024];   // local_1414 - Buffer for formatted message
    uint32_t dummyContext = 0;    // local_1014 - Placeholder for internal context
    char internalBuffer[0x1010];  // local_1010 - Internal buffer (cleared but not directly used here)
    
    // Clear internal buffer (likely used by the downstream logging function)
    _memset(internalBuffer, 0, sizeof(internalBuffer));
    
    // Format the message into a fixed-size buffer (max 1024 chars)
    __vsnprintf(formattedBuffer, sizeof(formattedBuffer), format, &stack0x00000010);
    
    // Forward to the actual log output function (0x00603610)
    // logContext is passed as &dummyContext?  (likely a temporary structure)
    // flags (param_2) are passed directly
    // formattedBuffer is the string to log
    // 0 is a constant (maybe log level or category)
    FUN_00603610(&dummyContext, flags, formattedBuffer, 0);
}