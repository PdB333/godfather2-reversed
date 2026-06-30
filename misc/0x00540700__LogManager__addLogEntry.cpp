// FUNC_NAME: LogManager::addLogEntry
// Address: 0x00540700
// Role: Enqueues a log entry into a fixed-size buffer; flushes when full or directly outputs if buffering disabled.
// Class: LogManager (EARS engine logging system)

void __thiscall LogManager::addLogEntry(int thisPtr, int logEntry)
{
    // +0x86c = bUseBufferedLogging (byte)
    if (*(char *)(thisPtr + 0x86c) != '\0') {
        // +0x868 = mLogCount (uint)
        uint logCount = *(uint *)(thisPtr + 0x868);
        if (logCount < 0x200) {
            // +0x68 = mLogBuffer (array of 0x200 uint32 slots)
            *(uint32 *)(thisPtr + 0x68 + logCount * 4) = logEntry;
            *(uint32 *)(thisPtr + 0x868) = logCount + 1;
        }
        if (*(uint32 *)(thisPtr + 0x868) == 0x200) {
            // Flush buffer when full (0x200 entries)
            LogBufferFlush(thisPtr + 0x68, 0x200);
            *(undefined4 *)(thisPtr + 0x868) = 0;
        }
        return;
    }
    // Direct output when buffering disabled
    LogWriteImmediate(&logEntry, logEntry);
}