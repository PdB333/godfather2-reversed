// FUNC_NAME: ConfigManager::ApplySettingsPreset
void ConfigManager::ApplySettingsPreset(byte presetLevel)
{
    // Adjust minimum quality setting to at least 25 (0x19)
    if (g_minQualityLevel < 25)
        g_minQualityLevel = 25;
    // Adjust maximum quality setting to at most 25 (0x19)
    if (g_maxQualityLevel > 25)
        g_maxQualityLevel = 25;
    g_unusedSetting5 = 5; // +0x3c? (global at 0x011f3a3c)

    // Further clamp minimum to at least 24 (0x18)
    if (g_minQualityLevel < 24)
        g_minQualityLevel = 24;
    // Further clamp maximum to at most 24 (0x18)
    if (g_maxQualityLevel > 24)
        g_maxQualityLevel = 24;
    g_presetLevel = (uint)presetLevel; // +0x38 (global at 0x011f3a38)

    // Final clamp minimum to at least 15 (0xf)
    if (g_minQualityLevel < 15)
        g_minQualityLevel = 15;
    // Final clamp maximum to at most 15 (0xf)
    if (g_maxQualityLevel > 15)
        g_maxQualityLevel = 15;
    g_enableFlag = 1; // +0x14 (global at 0x011f3a14)
}