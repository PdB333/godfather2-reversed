// FUNC_NAME: debugLogStoreEntry
void debugLogStoreEntry(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6)
{
    // Global counter for ring buffer (DAT_012058b0)
    static uint32_t g_logEntryIndex = 0;
    // Base address of log entry array (DAT_011f3918)
    static LogEntry* g_logEntries = (LogEntry*)0x011f3918;
    
    uint32_t idx = g_logEntryIndex * 0x18; // offset in bytes to current slot
    g_logEntries[idx + 0x00] = param1;      // offset 0x00
    g_logEntries[idx + 0x04] = param2;      // offset 0x04
    g_logEntries[idx + 0x08] = param3;      // offset 0x08
    g_logEntries[idx + 0x0C] = param4;      // offset 0x0C
    g_logEntries[idx + 0x10] = param5;      // offset 0x10
    g_logEntries[idx + 0x14] = param6;      // offset 0x14
    
    // Additional processing likely involving param4 and param6
    debugLogProcessEntry(param4, param6);
}

// Helper function (FUN_00609500) – not defined here but called.
extern void debugLogProcessEntry(uint32_t a, uint32_t b);