// FUNC_NAME: applyVideoSettings
void applyVideoSettings(void) {
    // Checks if display mode needs to be set
    if (g_currentDisplayMode == g_targetDisplayMode && g_displayModeFlags == 0) {
        setDisplayMode(1);
    } else {
        initDisplayMode(g_currentDisplayMode, g_targetDisplayMode);
    }

    // If target display index is valid, update display mode entry
    if (g_targetDisplayMode != 0xffffffff && g_targetDisplayMode < 0x1000) {
        int displayIndex = g_targetDisplayMode * 0x38; // stride 0x38
        byte* displayEntry = (byte*)(g_displayModeArray + displayIndex);
        if (displayEntry != nullptr && *displayEntry < 4) {
            int* pModeData = (int*)(g_displayModeArray + displayIndex + 0x1c);
            if (*pModeData != 0) {
                freeMemory(*pModeData, 0x200000);
            }
            uint* pFlags = (uint*)(g_displayModeArray + displayIndex + 0x0c);
            *pFlags = (*pFlags & 0xfcac8fff) | 0x200000;
            updateDisplayMode();
        }
    }

    // Set video quality limits and flags (multiple settings)
    if (g_brightnessMin < 0x16) g_brightnessMin = 0x16;
    if (0x16 < g_brightnessMax) g_brightnessMax = 0x16;
    g_settingBrightnessEnabled = 1;

    if (g_contrastMin < 7) g_contrastMin = 7;
    if (7 < g_contrastMax) g_contrastMax = 7;
    g_settingContrastEnabled = 0;

    if (g_saturationMin < 0xe) g_saturationMin = 0xe;
    if (0xe < g_saturationMax) g_saturationMax = 0xe;
    g_settingSaturationEnabled = 0;

    if (g_gammaMin < 0x19) g_gammaMin = 0x19;
    if (0x19 < g_gammaMax) g_gammaMax = 0x19;
    g_settingGammaEnabled = 5;

    if (g_sharpnessMin < 0x18) g_sharpnessMin = 0x18;
    if (0x18 < g_sharpnessMax) g_sharpnessMax = 0x18;
    g_settingSharpnessEnabled = 0;

    if (g_hueMin < 0xf) g_hueMin = 0xf;
    if (0xf < g_hueMax) g_hueMax = 0xf;
    g_settingHueEnabled = 0;

    if (g_colorTemperatureMin < 0x1b) g_colorTemperatureMin = 0x1b;
    if (0x1a < g_colorTemperatureMax) g_colorTemperatureMax = 0x1b;
    g_settingColorTempEnabled = 0;

    setVideoOutput(1, 2, 1);

    // Check graphics API preference
    if ((g_graphicsFlags & 0x400000) == 0) {
        g_selectedGraphicsAPI = g_graphicsAPIFallback;
    } else {
        g_selectedGraphicsAPI = g_graphicsAPIPreferred;
    }

    updateGraphicsConfiguration();
    setupRenderingPipeline();

    // If preferred API is selected, apply additional settings
    if (g_selectedGraphicsAPI == g_graphicsAPIPreferred) {
        if (g_enableShadows != 0) {
            applyShadowSettings();
        }
        if (g_selectedGraphicsAPI == g_graphicsAPIPreferred && g_enableAntialiasing != 0) {
            applyAntialiasingSettings();
        }
    }

    setResolution(g_resolutionX, g_resolutionY, g_resolutionBPP);

    if (g_selectedGraphicsAPI == g_graphicsAPIPreferred) {
        applyAspectRatio(g_selectedGraphicsAPI, g_displayRefreshRate, &g_overrideResolution);
    }

    // Allocate and fill video configuration structure
    uint* videoConfig = (uint*)allocateMemory(0xd, 4, 0, 1, 0);
    uint valA = g_videoConfigA;
    uint valB = g_videoConfigB;
    if (videoConfig != nullptr) {
        videoConfig[0] = g_videoConfigA;
        videoConfig[1] = valB;
        videoConfig[2] = 0;
        videoConfig[3] = 0;
        videoConfig[4] = valB;
        videoConfig[5] = valB;
        videoConfig[6] = valB;
        videoConfig[7] = 0;
        videoConfig[8] = valB;
        videoConfig[9] = valA;
        videoConfig[10] = valB;
        videoConfig[11] = valB;
        videoConfig[12] = valA;
        videoConfig[13] = valA;
        videoConfig[14] = 0;
        videoConfig[15] = valB;
        finalizeVideoConfig();
    }

    finalizeSettings();

    // Reapply limits with different flags (probably second pass)
    if (g_brightnessMin < 0x16) g_brightnessMin = 0x16;
    if (0x16 < g_brightnessMax) g_brightnessMax = 0x16;
    g_settingBrightnessEnabled = 1;

    if (g_contrastMin < 7) g_contrastMin = 7;
    if (7 < g_contrastMax) g_contrastMax = 7;
    g_settingContrastEnabled = 1;

    if (g_saturationMin < 0xe) g_saturationMin = 0xe;
    if (0xe < g_saturationMax) g_saturationMax = 0xe;
    g_settingSaturationEnabled = 1;

    if (g_gammaMin < 0x19) g_gammaMin = 0x19;
    if (0x19 < g_gammaMax) g_gammaMax = 0x19;
    g_settingGammaEnabled = 7;

    if (g_sharpnessMin < 0x18) g_sharpnessMin = 0x18;
    if (0x18 < g_sharpnessMax) g_sharpnessMax = 0x18;
    g_settingSharpnessEnabled = 0;

    if (g_hueMin < 0xf) g_hueMin = 0xf;
    if (0xf < g_hueMax) g_hueMax = 0xf;
    g_settingHueEnabled = 0;

    if (g_colorTemperatureMin < 0x1b) g_colorTemperatureMin = 0x1b;
    if (0x1a < g_colorTemperatureMax) g_colorTemperatureMax = 0x1b;
    g_settingColorTempEnabled = 0;

    setVideoOutput(1, 5, 6);
}