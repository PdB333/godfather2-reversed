// FUNC_NAME: DebugManager::dispatchCommandIfEnabled
// Address: 0x005e2a80
// Role: Forwards a debug command (ID 0x32) to internal handler if debug mode is enabled.
// The global g_pDebugManager points to a DebugManager instance; offset 0x1744 is m_bDebugEnabled flag.

void DebugManager::dispatchCommandIfEnabled(int param1, int param2, int param3) {
    // Check if debug mode is active
    if (*(char*)(g_pDebugManager + 0x1744) != '\0') {
        // Internal command handler with command ID 0x32 (50)
        DebugManager::internalCommandHandler(g_pDebugManager, param1, param2, param3, 0x32);
    }
}