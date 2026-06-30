// FUNC_NAME: resetDebugStatsData
void resetDebugStatsData(void)
{
    // Global float variables at 0x01125230, 0x01125234, 0x01125238, 0x0112523c
    g_debugFloat1 = g_debugFloat1 * 0.0f;
    g_debugFloat2 = g_debugFloat2 * 0.0f;
    g_debugFloat3 = g_debugFloat3 * 0.0f;
    g_debugFloat4 = g_debugFloat4 * 0.0f;
    // Global int variable at 0x01125240
    g_debugInt = 0;
}