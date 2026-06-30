// FUNC_NAME: initializeVideoQualityPresets
void initializeVideoQualityPresets(char param_1)
{
    // Call some system initialization (likely platform-specific)
    platformInit();

    // Clear a set of flags/state variables (preset index or quality flags)
    g_qualityFlags[0] = 0;  // +0x04 ?
    g_qualityFlags[1] = 0;  // +0x08 ?
    g_qualityFlags[2] = 0;  // +0x0C ?
    g_qualityFlags[3] = 0;  // +0x10 ?
    g_qualityFlags[4] = 0;  // +0x14 ?
    g_qualityFlags[5] = 0;  // +0x18 ?
    g_qualityFlags[6] = 0;  // +0x1C ?

    if (param_1 != '\0')  // If high quality preset is requested
    {
        // Likely set resolution/display mode
        setDisplayMode(&g_mainDisplayMode);

        // Adjust min/max quality settings (clamping to preset values)
        // These globals (DAT_012058d0 and DAT_00f15988) seem to represent
        // minimum and maximum allowed quality levels (e.g., detail, shadows, etc.)

        // Preset 1: Shadow quality? Or texture quality?
        if (g_minQualitySetting < 0x16)
            g_minQualitySetting = 0x16;
        if (g_maxQualitySetting > 0x16)   // note: condition is > 0x16 (likely max cap)
            g_maxQualitySetting = 0x16;
        g_qualityPreset[0] = 1;  // +0x30 ?

        // Preset 2: Another setting
        if (g_minQualitySetting < 0x19)
            g_minQualitySetting = 0x19;
        if (g_maxQualitySetting > 0x19)
            g_maxQualitySetting = 0x19;
        g_qualityPreset[3] = 7;  // +0x3C ?

        // Preset 3: Setting index +0x38
        if (g_minQualitySetting < 0x18)
            g_minQualitySetting = 0x18;
        if (g_maxQualitySetting > 0x18)
            g_maxQualitySetting = 0x18;
        g_qualityPreset[2] = 0;  // +0x38 ?

        // Preset 4: Setting index +0x14
        if (g_minQualitySetting < 0xF)
            g_minQualitySetting = 0xF;
        if (g_maxQualitySetting > 0xF)
            g_maxQualitySetting = 0xF;
        g_qualityPreset[4] = 0;  // +0x14 ?

        // Preset 5: Setting index +0xF4? (offset 0x1f4? Actually 0x1f4 is not correct, maybe off)
        // Wait, offset is 0x1f4? Actually _DAT_011f39f4 is at 0x011f39f4, relative to some base.
        // For now, use indices.
        if (g_minQualitySetting < 7)
            g_minQualitySetting = 7;
        if (g_maxQualitySetting > 7)
            g_maxQualitySetting = 7;
        g_qualityPreset[5] = 1;  // +0x1F4? No, we'll just use array.

        // Preset 6: Setting index +0x10
        if (g_minQualitySetting < 0xE)
            g_minQualitySetting = 0xE;
        if (g_maxQualitySetting > 0xE)
            g_maxQualitySetting = 0xE;
        g_qualityPreset[6] = 1;  // +0x10 ?

        // Preset 7: Setting index +0x44
        if (g_minQualitySetting < 0x1B)
            g_minQualitySetting = 0x1B;
        if (g_maxQualitySetting > 0x1B)
            g_maxQualitySetting = 0x1B;
        g_qualityPreset[7] = 0;  // +0x44 ?

        // Apply/commit the settings with specific parameters (1,5,6)
        // Possibly "applyQualityPreset(1,5,6)" where arguments are indices or flags
        applyQualitySettings(1, 5, 6);
    }
    return;
}