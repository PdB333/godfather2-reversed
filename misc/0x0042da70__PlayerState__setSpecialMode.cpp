// FUNC_NAME: PlayerState::setSpecialMode
void __thiscall PlayerState::setSpecialMode(int mode)
{
    // Global state related to health thresholds and cheat mode
    extern bool g_cheatsEnabled;          // DAT_00e79b5c
    extern int g_playerMinHealth;         // DAT_012058d0 (minimum health threshold)
    extern int g_playerMaxHealth;         // DAT_00f15988 (maximum health threshold)
    extern int g_healthMode;              // _DAT_011f3a30 (0/2/3, mode indicator)

    static const int kBaseThreshold = 22; // 0x16

    if (!g_cheatsEnabled)
        return;

    if (mode == 1)
    {
        // Mode 1: enforce thresholds and set special flag A
        if (g_playerMinHealth < kBaseThreshold)
            g_playerMinHealth = kBaseThreshold;
        if (kBaseThreshold < g_playerMaxHealth)
            g_playerMaxHealth = kBaseThreshold;
        g_healthMode = 3;
        this->flags |= 0x20000; // Bit 17 - enables special behavior A
        return;
    }

    // Mode != 1: enforce thresholds and set special flag B
    if (g_playerMinHealth < kBaseThreshold)
        g_playerMinHealth = kBaseThreshold;
    if (kBaseThreshold < g_playerMaxHealth)
        g_playerMaxHealth = kBaseThreshold;
    this->flags |= 0x10000; // Bit 16 - enables special behavior B
    g_healthMode = 2;
}