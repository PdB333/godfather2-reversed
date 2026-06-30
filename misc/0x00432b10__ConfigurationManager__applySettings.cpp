// FUNC_NAME: ConfigurationManager::applySettings
// Address: 0x00432b10
// Role: Applies quality configuration from a settings structure to global engine state.

void ConfigurationManager::applySettings(int thisPtr) {
    // Clamp global quality range minimum to 14 (0xE)
    if (g_minQualityLevel < 0xE) {
        g_minQualityLevel = 0xE;
    }
    // Also cap the maximum quality level to 14 (0xE) if it exceeds that
    if (0xE < g_maxQualityLevel) {
        g_maxQualityLevel = 0xE;
    }
    g_qualitySetting1 = 1; // +0x10? Shadow quality low

    // Clamp again to 23 (0x17)
    if (g_minQualityLevel < 0x17) {
        g_minQualityLevel = 0x17;
    }
    if (0x17 < g_maxQualityLevel) {
        g_maxQualityLevel = 0x17;
    }
    g_qualitySetting2 = 4; // +0x34? Texture quality medium

    // Clamp to 7
    if (g_minQualityLevel < 7) {
        g_minQualityLevel = 7;
    }
    if (7 < g_maxQualityLevel) {
        g_maxQualityLevel = 7;
    }
    g_qualitySetting3 = 1; // +0x3F4? Antialiasing off

    // Call setDetailQuality(1,5,6) – resolution or LoD
    setDetailQuality(1, 5, 6);

    // Clamp to 27 (0x1B)
    if (g_minQualityLevel < 0x1B) {
        g_minQualityLevel = 0x1B;
    }
    if (0x1A < g_maxQualityLevel) {
        g_maxQualityLevel = 0x1B;
    }
    g_qualitySetting4 = 0; // +0x44? VSync off

    // Clamp to 25 (0x19)
    if (g_minQualityLevel < 0x19) {
        g_minQualityLevel = 0x19;
    }
    if (0x19 < g_maxQualityLevel) {
        g_maxQualityLevel = 0x19;
    }
    g_qualitySetting5 = 7; // +0x3C? Anisotropic filtering level

    // Clamp to 24 (0x18)
    if (g_minQualityLevel < 0x18) {
        g_minQualityLevel = 0x18;
    }
    if (0x18 < g_maxQualityLevel) {
        g_maxQualityLevel = 0x18;
    }
    g_qualitySetting6 = 0; // +0x38? Motion blur off

    // Clamp to 15 (0xF)
    if (g_minQualityLevel < 0xF) {
        g_minQualityLevel = 0xF;
    }
    if (0xF < g_maxQualityLevel) {
        g_maxQualityLevel = 0xF;
    }
    g_qualitySetting7 = 0; // +0x14? Bloom off

    // Clamp to 22 (0x16)
    if (g_minQualityLevel < 0x16) {
        g_minQualityLevel = 0x16;
    }
    if (0x16 < g_maxQualityLevel) {
        g_maxQualityLevel = 0x16;
    }
    g_qualitySetting8 = 1; // +0x30? HDR on

    // Apply the rendering mode (FUN_00609890 = setRenderMode)
    setRenderMode(1);

    // Save old render resolution and set new from settings
    int oldWidth = g_currentRenderX;   // DAT_011f38f0
    int oldHeight = g_currentRenderY;  // DAT_011f38f4
    g_currentRenderX = *(int *)(thisPtr + 0x80);  // +0x80 = width
    g_currentRenderY = 0;
    // Change resolution (FUN_00609340 = changeResolution)
    changeResolution(0, oldWidth, oldHeight);

    // Set frame rate limit to 15 (0xF)
    setFrameRateLimit(0xF);

    // If the "single player" flag is set, load the game audio settings
    if (*(int *)(thisPtr + 0x39F8) == 1) {
        loadAudioSettings(*(int *)(thisPtr + 0x1098));
    }
    return;
}