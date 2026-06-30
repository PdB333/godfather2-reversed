// FUNC_NAME: DebugManager::debugLog
// Address: 0x005e2a80
// Role: Checks if debugging is enabled (global flag at offset 0x1744) and if so,
//       calls the internal logging function with a log level of 50 (0x32).
// Global pointer DAT_0122350c is assumed to point to the DebugManager singleton.
void DebugManager::debugLog(int a1, int a2, int a3)
{
    // Offset 0x1744 in the debug manager is a boolean flag indicating debug logging is active.
    if (*(char*)(DAT_0122350c + 0x1744) != '\0')
    {
        // Call the internal logging function (FUN_005e25f0) with the debug manager instance,
        // the three user parameters, and log level 0x32 (50).
        // The inner function likely handles formatting and output.
        FUN_005e25f0(DAT_0122350c, a1, a2, a3, 0x32);
    }
}