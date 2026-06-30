// Xbox PDB: SM_PrimTexturedClass::SelectTextureMode
// FUNC_NAME: applyGraphicsQualityPreset

void applyGraphicsQualityPreset(char applyHighQuality) {
    if (applyHighQuality) {
        // Force high-quality settings for all features
        // Each block sets min/max threshold to a specific value and assigns a flag

        // Feature 1: quality level 0x16 (22)
        if (g_qualityMin < 0x16) {
            g_qualityMin = 0x16;
        }
        if (0x16 < g_qualityMax) {
            g_qualityMax = 0x16;
        }
        g_qualityFlags[0] = 1; // _DAT_011f3a30

        // Feature 2: quality level 0x19 (25)
        if (g_qualityMin < 0x19) {
            g_qualityMin = 0x19;
        }
        if (0x19 < g_qualityMax) {
            g_qualityMax = 0x19;
        }
        g_qualityFlags[1] = 7; // _DAT_011f3a3c

        // Feature 3: quality level 0x18 (24)
        if (g_qualityMin < 0x18) {
            g_qualityMin = 0x18;
        }
        if (0x18 < g_qualityMax) {
            g_qualityMax = 0x18;
        }
        g_qualityFlags[2] = 1; // _DAT_011f3a38

        // Feature 4: quality level 0xF (15)
        if (g_qualityMin < 0xf) {
            g_qualityMin = 0xf;
        }
        if (0xf < g_qualityMax) {
            g_qualityMax = 0xf;
        }
        g_qualityFlags[3] = 1; // _DAT_011f3a14

        // Feature 5: quality level 7
        if (g_qualityMin < 7) {
            g_qualityMin = 7;
        }
        if (7 < g_qualityMax) {
            g_qualityMax = 7;
        }
        g_qualityFlags[4] = 0; // _DAT_011f39f4

        // Feature 6: quality level 0xE (14)
        if (g_qualityMin < 0xe) {
            g_qualityMin = 0xe;
        }
        if (0xe < g_qualityMax) {
            g_qualityMax = 0xe;
        }
        g_qualityFlags[5] = 0; // _DAT_011f3a10

        // Feature 7: quality level 0x1B (27)
        if (g_qualityMin < 0x1b) {
            g_qualityMin = 0x1b;
        }
        if (0x1b < g_qualityMax) {
            g_qualityMax = 0x1b;
        }
        g_qualityFlags[6] = 1; // _DAT_011f3a44

        // Apply quality settings to rendering pipeline
        setRenderState(1, 5, 6);
        initializeGraphicsBackend(&g_graphicsState);
    }

    // Load LOD bias from configuration
    g_configHandle = g_configDocument; // DAT_01127774 = DAT_01127878
    g_lodBiasSetting = getConfigSetting(g_configDocument, "lodBias"); // returns key index

    if (g_graphicsDevice == &PTR_PTR_01127760) {
        releaseConfig(g_configHandle);
        applyConfigSetting(g_configHandle, g_lodBiasSetting, g_lodBiasValue);
    }

    syncRenderQueue();
}