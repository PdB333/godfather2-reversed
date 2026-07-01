// FUNC_NAME: DebugManager::triggerDebugLog
// Function address: 0x007bacb0
// Role: When debug mode is active, packs three parameters into 64-bit fields and calls the debug output function.
// Called from FUN_007bb860 (likely a debug input handler).

// Forward declarations for helper functions at known addresses
bool isDebugModeEnabled();          // 0x00481660 - returns nonzero if debug logging is enabled
void debugOutputRaw(uint arg1,      // 0x0079fb90 - writes packed debug data
                    uint64 arg2,
                    uint64 arg3,
                    uint64 arg4,
                    uint arg5);

void DebugManager::triggerDebugLog(uint param1, char param2, char param3)
{
    if (isDebugModeEnabled())
    {
        uint localFlag = 1; // set bit0 of the low parameter field (marks event type)
        // arg1 = 0 (channel or unused)
        // arg2 = high dword = 1 (command), low dword = localFlag (sub‑command)
        // arg3 = high dword = param2 (extended flag), low dword = param1 (primary id)
        // arg4, arg5 = zeroed (stack garbage ignored)
        debugOutputRaw(
            0,
            ((uint64)1 << 32) | localFlag,
            ((uint64)(uint8)param2 << 32) | param1,
            0,
            0
        );
    }
}