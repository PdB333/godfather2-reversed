// FUNC_NAME: setFrameRateCap
void setFrameRateCap(int newValue)
{
    // Global: g_frameRateMin at 0x012058d0, g_frameRateMax at 0x00f15988, g_frameRateTarget at 0x011f3ac4
    if (g_frameRateMin < 0x3b) {
        g_frameRateMin = 0x3b;
    }
    if (g_frameRateMax > 0x3b) {
        g_frameRateMax = 0x3b;
        g_frameRateTarget = newValue;
        return;
    }
    g_frameRateTarget = newValue;
}