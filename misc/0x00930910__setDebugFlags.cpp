// FUNC_NAME: setDebugFlags
void setDebugFlags(char enable)
{
    if (enable != '\0') {
        // Set bit 0x2000 (likely a specific debug flag)
        g_debugFlags = g_debugFlags | 0x2000;
        return;
    }
    // Set bit 0x20 (another debug flag)
    g_debugFlags = g_debugFlags | 0x20;
    return;
}