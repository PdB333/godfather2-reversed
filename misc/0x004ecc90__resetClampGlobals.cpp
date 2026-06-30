// FUNC_NAME: resetClampGlobals
void resetClampGlobals(void)
{
    // Clamp g_minLimit to at least 14 (likely a minimum number of something, e.g., territories or missions)
    if (g_minLimit < 14) {
        g_minLimit = 14;
    }

    // Reset some global flag to 0 (likely indicating a state or count)
    g_resetFlag = 0;

    // Clamp g_maxLimit to at most 14 (upper bound for a game parameter)
    if (14 < g_maxLimit) {
        g_maxLimit = 14;
    }
}