// FUNC_NAME: DebugEventLog

void DebugEventLog(int param1, int param2, int param3)
{
    // Increment event counter and store three parameters
    g_debugEventCount++;
    g_debugEventParam1 = param1;
    g_debugEventParam2 = param2;
    g_debugEventParam3 = param3;
}

// Global variables used by DebugEventLog
extern int g_debugEventCount;
extern int g_debugEventParam1;
extern int g_debugEventParam2;
extern int g_debugEventParam3;