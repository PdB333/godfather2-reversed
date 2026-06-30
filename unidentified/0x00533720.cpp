// FUN_00533720: SettingsManager::applySafeDefaultSettings
void SettingsManager::applySafeDefaultSettings(void* settingsObject)
{
    // Call engine base initialization
    unknownInitFunction();

    // Reset global configuration flags
    g_optionFlags1 = 0;   // _DAT_01219b24
    g_optionFlags2 = 0;   // _DAT_01219b28
    g_optionFlags3 = 0;   // _DAT_01219b2c

    // Clamp minimum gamma/quality value upward
    if (g_minGamma < 0x1b) g_minGamma = 0x1b;
    // Clamp maximum gamma/quality value downward
    if (0x1a < g_maxGamma) g_maxGamma = 0x1b;

    g_anotherFlag = 0;    // _DAT_011f3a44

    if (g_minGamma < 0x19) g_minGamma = 0x19;
    if (0x19 < g_maxGamma) g_maxGamma = 0x19;

    g_renderMode = 7;     // _DAT_011f3a3c

    if (g_minGamma < 0x18) g_minGamma = 0x18;
    if (0x18 < g_maxGamma) g_maxGamma = 0x18;

    g_qualityLevel = 0;   // _DAT_011f3a38

    if (g_minGamma < 0x0f) g_minGamma = 0x0f;
    if (0x0f < g_maxGamma) g_maxGamma = 0x0f;

    g_textureBias = 0;    // _DAT_011f3a14

    if (g_minGamma < 0x0e) g_minGamma = 0x0e;
    if (0x0e < g_maxGamma) g_maxGamma = 0x0e;

    g_shadowFlags = 1;    // _DAT_011f3a10

    if (g_minGamma < 7) g_minGamma = 7;
    if (7 < g_maxGamma) g_maxGamma = 7;

    g_antialiasing = 1;   // _DAT_011f39f4

    if (g_minGamma < 0x16) g_minGamma = 0x16;
    if (0x16 < g_maxGamma) g_maxGamma = 0x16;

    g_postProcess = 1;    // _DAT_011f3a30

    // Set rendering mode (param1=1, param2=5, param3=6)
    setRenderMode(1, 5, 6);

    // If the settings object has its first bit set at offset +8, apply specific settings
    if ((*(uint8_t*)((uintptr_t)settingsObject + 8) & 1) != 0)
    {
        applySpecificSettings(0, 0);
    }
}