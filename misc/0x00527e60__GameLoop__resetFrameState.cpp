// FUNC_NAME: GameLoop::resetFrameState

void resetFrameState(void)
{
    // Check if we should process some action based on current time or flag
    // g_currentTime <= g_throttleTimer1 && g_currentTime <= g_throttleTimer2
    // OR a specific flag (0x400000) is set
    if ((g_currentTime <= g_throttleTimer1 && g_currentTime <= g_throttleTimer2) ||
        (g_frameFlags & 0x400000) != 0)
    {
        // Call the specific processing function (likely handles frame throttling or state update)
        processFrameAction();  // FUN_005279e0
    }

    // Reset frame timers and counters
    g_throttleTimer1 = 0.0f;
    g_throttleTimer2 = 0.0f;
    g_frameCounter1 = 0;
    g_frameCounter2 = 0;

    // Reset position/state values from cached constants
    g_cachedPositionX = g_basePositionX;   // DAT_00e2b118
    g_cachedPositionY = g_basePositionY;   // DAT_00e2b1a4
    g_cachedSpeed = g_baseSpeed;           // DAT_00e446c4
    g_cachedRotation = g_basePositionY;    // reusing same base

    // Clear flags
    g_frameFlags = 0;
}