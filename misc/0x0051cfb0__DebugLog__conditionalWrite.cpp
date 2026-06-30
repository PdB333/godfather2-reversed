// FUNC_NAME: DebugLog::conditionalWrite
// Address: 0x0051cfb0
// Role: Conditional debug log output - writes a formatted message to a local buffer if a global debug flag is enabled
// Called by: 0x0051d450 (likely a debug update or frame function)
// Assumes:
//   - FUN_00577f40() returns non-zero when debug logging is active (boolean check)
//   - FUN_0044b4e0(int value, char* buffer) formats some debug text into buffer (12 bytes max)
//   - DAT_00e2b1a4 is a global constant (e.g., debug category mask or listener pointer)
//   - param_1 is unused – possibly a channel/level that is ignored in this build

void DebugLog::conditionalWrite(int unusedChannel, int messageValue)
{
    // Temporary buffer for formatted debug output (12 bytes – likely enough for a short diagnostic)
    char debugBuffer[12];
    
    // Stack‑local state (initialized but not used directly in this function)
    // May be part of a stack‑passed struct or alignment padding for the format call
    int structDummy1 = 0;   // +0x00
    int structDummy2 = 0;   // +0x04
    int structDummy3 = 0;   // +0x08
    int debugListenerOrMask = DAT_00e2b1a4; // +0x0C – global debug configuration
    
    // Only attempt to write the debug message if the logging system is active
    if (isDebugLoggingEnabled())
    {
        // Format the debug message using the provided value and the temporary buffer
        formatDebugMessage(messageValue, debugBuffer);
    }
    
    // Note: The local buffer is not used after the conditional call – it may be
    // consumed inside formatDebugMessage or discarded (e.g., hex dump to log file).
    return;
}