// FUNC_NAME: DifficultyManager::initializeDefaults
void DifficultyManager::initializeDefaults(DifficultyManager* thisPtr)
{
    // Reset global configuration
    FUN_00612e00();

    // Initialize fields in a config structure (addresses are global statics)
    g_configField1 = 0;  // _DAT_01219b24
    g_configField2 = 0;  // _DAT_01219b28
    g_configField3 = 0;  // _DAT_01219b2c

    // Clamp minimum difficulty (0x1b = 27)
    if (g_minDifficulty < 27) {
        g_minDifficulty = 27;  // DAT_012058d0
    }
    // Clamp maximum difficulty (0x1b = 27)
    if (g_maxDifficulty > 27) {  // DAT_00f15988
        g_maxDifficulty = 27;
    }
    g_configField4 = 0;  // _DAT_011f3a44

    // Next level clamp (0x19 = 25)
    if (g_minDifficulty < 25) {
        g_minDifficulty = 25;
    }
    if (g_maxDifficulty > 25) {
        g_maxDifficulty = 25;
    }
    g_configField5 = 7;  // _DAT_011f3a3c

    // Next level clamp (0x18 = 24)
    if (g_minDifficulty < 24) {
        g_minDifficulty = 24;
    }
    if (g_maxDifficulty > 24) {
        g_maxDifficulty = 24;
    }
    g_configField6 = 0;  // _DAT_011f3a38

    // Next level clamp (0xf = 15)
    if (g_minDifficulty < 15) {
        g_minDifficulty = 15;
    }
    if (g_maxDifficulty > 15) {
        g_maxDifficulty = 15;
    }
    g_configField7 = 0;  // _DAT_011f3a14

    // Next level clamp (0xe = 14)
    if (g_minDifficulty < 14) {
        g_minDifficulty = 14;
    }
    if (g_maxDifficulty > 14) {
        g_maxDifficulty = 14;
    }
    g_configField8 = 1;  // _DAT_011f3a10

    // Next level clamp (7)
    if (g_minDifficulty < 7) {
        g_minDifficulty = 7;
    }
    if (g_maxDifficulty > 7) {
        g_maxDifficulty = 7;
    }
    g_configField9 = 1;  // _DAT_011f39f4

    // Next level clamp (0x16 = 22)
    if (g_minDifficulty < 22) {
        g_minDifficulty = 22;
    }
    if (g_maxDifficulty > 22) {
        g_maxDifficulty = 22;
    }
    g_configField10 = 1;  // _DAT_011f3a30

    // Set some global parameter with three args
    FUN_00417cf0(1, 5, 6);

    // Optional reset if a flag in the object is set (bit 0 at offset +8)
    if ((thisPtr->flags & 1) != 0) {
        FUN_0041e660(0, 0);
    }
}