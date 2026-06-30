// FUNC_NAME: ConnectionManager::finalizeShutdown
/* Address: 0x006061a0
   Role: Final cleanup/shutdown check for connection manager.
   Enters critical section, sets state to 4 (shutting down),
   then checks if all connections are closed (count == 63, no pending, no flags)
   and advances count to 64 (fully shut down). */

void ConnectionManager::finalizeShutdown(void)
{
    LPCRITICAL_SECTION pCritSec = g_pConnectionCriticalSection; // DAT_011d917c

    EnterCriticalSection(pCritSec);
    // Clear the highest bit (bit 31) of connection flags (maybe stop bit)
    g_connectionFlags &= 0x7fffffff; // _DAT_011d9124
    g_connectionState = 4; // DAT_011d8ef0, 4 = STATE_SHUTTING_DOWN
    // Check if all connections are idle: count == 63, no pending work, no flags
    if ((g_connectionCount == 0x3f) &&               // DAT_011d9128
        (g_connectionPending == 0) &&                // DAT_011d9120
        (g_connectionFlags == 0))                    // _DAT_011d9124 (already cleared, but read again? may be separate variable)
    {
        g_connectionCount = 0x40; // Advance to fully shut down state
    }
    LeaveCriticalSection(pCritSec);
}