// FUNC_NAME: checkAndLogDebugMessage
// Address: 0x00967f90
// Role: Checks if debug logging is enabled and logs a message with level 0xB.

// Global pointer to debug manager (likely DebugManager*)
extern DebugManager* g_debugManager; // DAT_01223484

// Forward declaration of log function (FUN_008b5cb0)
void logMessage(const char* message, int level);

void checkAndLogDebugMessage(void)
{
    if (g_debugManager != nullptr && *(int*)((char*)g_debugManager + 0xC) != 0) // +0x0C: isLoggingEnabled flag
    {
        logMessage("PTR_LAB_00d79770", 0xB); // 0xB = 11, likely a log level (e.g., kLogDebug)
    }
}