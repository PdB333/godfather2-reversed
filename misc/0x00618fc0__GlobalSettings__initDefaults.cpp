// FUNC_NAME: GlobalSettings::initDefaults
void GlobalSettings::initDefaults(void) {
    // Clamp global version thresholds to 0x16
    if (g_uiVersionMin < 0x16) {
        g_uiVersionMin = 0x16;
    }
    if (0x16 < g_uiVersionMax) {
        g_uiVersionMax = 0x16;
    }

    // Default setting flags (block 1)
    g_bSetting1 = 1;           // +0x30
    g_bSetting2 = 1;           // +0xDC
    g_bSetting3 = 1;           // +0xE0
    g_bSetting4 = 1;           // +0xE4
    g_bSetting5 = 1;           // +0xE8
    g_bSetting6 = 0;           // +0xEC
    g_bSetting7 = 1;           // +0xF8
    g_iSetting8 = 0xFF;        // +0xF0
    g_iSetting9 = 0xFF;        // +0xF4

    initAudioSystem();          // sub_00619210

    // Clamp to 0x34
    if (g_uiVersionMin < 0x34) {
        g_uiVersionMin = 0x34;
    }
    if (0x34 < g_uiVersionMax) {
        g_uiVersionMax = 0x34;
    }
    g_iSetting11 = 0;           // +0xA8

    setGraphicsMode(1, 1, 1);   // sub_0041e4d0

    // Clamp to 0x38
    if (g_uiVersionMin < 0x38) {
        g_uiVersionMin = 0x38;
    }
    if (0x38 < g_uiVersionMax) {
        g_uiVersionMax = 0x38;
    }
    g_iSetting14 = 8;           // +0xB8

    // Clamp to 0x39
    if (g_uiVersionMin < 0x39) {
        g_uiVersionMin = 0x39;
    }
    if (0x39 < g_uiVersionMax) {
        g_uiVersionMax = 0x39;
    }
    g_iSetting15 = 0;           // +0xBC

    // Clamp to 0x3A
    if (g_uiVersionMin < 0x3A) {
        g_uiVersionMin = 0x3A;
    }
    if (0x3A < g_uiVersionMax) {
        g_uiVersionMax = 0x3A;
    }
    g_iSetting16 = -1;          // +0xC0

    setControlScheme(1, 5, 6); // sub_00417cf0

    // Clamp to 0x19
    if (g_uiVersionMin < 0x19) {
        g_uiVersionMin = 0x19;
    }
    if (0x19 < g_uiVersionMax) {
        g_uiVersionMax = 0x19;
    }
    g_iSetting17 = 7;           // +0x3C

    // Clamp to 0x18
    if (g_uiVersionMin < 0x18) {
        g_uiVersionMin = 0x18;
    }
    if (0x18 < g_uiVersionMax) {
        g_uiVersionMax = 0x18;
    }
    g_iSetting18 = 0;           // +0x38

    // Clamp to 0x0F
    if (g_uiVersionMin < 0x0F) {
        g_uiVersionMin = 0x0F;
    }
    if (0x0F < g_uiVersionMax) {
        g_uiVersionMax = 0x0F;
    }
    g_iSetting19 = 0;           // +0x14

    // Clamp to 0x1B
    if (g_uiVersionMin < 0x1B) {
        g_uiVersionMin = 0x1B;
    }
    if (0x1A < g_uiVersionMax) { // Note: condition uses 0x1A but sets to 0x1B
        g_uiVersionMax = 0x1B;
    }
    g_iSetting20 = 0;           // +0x44

    // Clamp to 0x07
    if (g_uiVersionMin < 7) {
        g_uiVersionMin = 7;
    }
    if (7 < g_uiVersionMax) {
        g_uiVersionMax = 7;
    }
    g_bSetting21 = 1;           // +0xF4? Actually +0xF4 is already used. Let's assign +0x14? No. g_iSetting19 was +0x14. Check decompile: _DAT_011f39f4 -> offset 0x14? Actually 0x011f39f4 - 0x011f39e0 = 0x14? Not sure. We'll keep names consistent but note offsets.

    // Clamp to 0x17
    if (g_uiVersionMin < 0x17) {
        g_uiVersionMin = 0x17;
    }
    if (0x17 < g_uiVersionMax) {
        g_uiVersionMax = 0x17;
    }
    g_iSetting23 = 4;           // +0x34

    // Final clamp to 0x0E
    if (g_uiVersionMin < 0x0E) {
        g_uiVersionMin = 0x0E;
    }
    g_bSetting24 = 1;           // +0x10
    g_bSetting25 = 1;           // +0x86 (DAT_01205886)
    if (0x0E < g_uiVersionMax) {
        g_uiVersionMax = 0x0E;
    }

    return;
}