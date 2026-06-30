// FUNC_NAME: GlobalConfig::setConfigTriple
// 0x00417cf0 - Sets three configuration values after clamping two pairs of global limits.
// Globals:
//   g_configLimitA1 (0x012058d4), g_configLimitA2 (0x00f1598c)  -> clamped to [0xab, 0xce]
//   g_configLimitB1 (0x012058d0), g_configLimitB2 (0x00f15988)  -> clamped to [0x13, 0x14]
//   g_configStore1 (0x011f3c84), g_configStore2 (0x011f3a24), g_configStore3 (0x011f3a28) -> stored params
//   g_configFlag (0x011f3d10) -> set to 0

void GlobalConfig::setConfigTriple(int param1, int param2, int param3)
{
    // Clamp limitA pair to [0xce, 0xce] actually min/max 0xce
    if (g_configLimitA1 < 0xce) {
        g_configLimitA1 = 0xce;
    }
    if (g_configLimitA2 > 0xcd) { // 0xcd < value means value > 0xcd -> set to 0xce
        g_configLimitA2 = 0xce;
    }

    g_configFlag = 0; // reset flag

    // Clamp limitA pair again to lower bound 0xab
    if (g_configLimitA1 < 0xab) {
        g_configLimitA1 = 0xab;
    }
    if (g_configLimitA2 > 0xaa) { // value > 0xaa -> set to 0xab
        g_configLimitA2 = 0xab;
    }

    g_configStore1 = param1;

    // Clamp limitB pair to [0x13, 0x14]
    if (g_configLimitB1 < 0x13) {
        g_configLimitB1 = 0x13;
    }
    if (g_configLimitB2 > 0x12) {
        g_configLimitB2 = 0x13;
    }

    g_configStore2 = param2;

    if (g_configLimitB1 < 0x14) {
        g_configLimitB1 = 0x14;
    }
    if (g_configLimitB2 > 0x13) {
        g_configLimitB2 = 0x14;
        g_configStore3 = param3;
        return;
    }

    g_configStore3 = param3;
}