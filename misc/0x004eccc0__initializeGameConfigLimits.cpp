// FUNC_NAME: initializeGameConfigLimits

void initializeGameConfigLimits(byte param_1)
{
    if (g_minConfig < 0x19) {
        g_minConfig = 0x19;
    }
    if (0x19 < g_maxConfig) {
        g_maxConfig = 0x19;
    }
    g_baseValue = 5;
    if (g_minConfig < 0x18) {
        g_minConfig = 0x18;
    }
    if (0x18 < g_maxConfig) {
        g_maxConfig = 0x18;
    }
    g_paramFlag = (uint)param_1;
    if (g_minConfig < 0xf) {
        g_minConfig = 0xf;
    }
    g_activationFlag = 1;
    if (0xf < g_maxConfig) {
        g_maxConfig = 0xf;
    }
    return;
}