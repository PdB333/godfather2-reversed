// FUN_NAME: initGameplayConfig
void initGameplayConfig(void)
{
    // Clamp the quality range to at least 22 and at most 22 (effectively setting to 22)
    if (g_minQuality < 0x16) {
        g_minQuality = 0x16;
    }
    if (0x16 < g_maxQuality) {
        g_maxQuality = 0x16;
    }

    // Set miscellaneous global flags to defaults
    g_flag1 = 1;
    g_flag2 = 1;
    g_flag3 = 1;
    g_flag4 = 1;
    g_flag5 = 1;
    g_flag6 = 0;
    g_flag7 = 1;
    g_byte1 = 0xff;
    g_byte2 = 0xff;

    // Call sub-initializer
    subInit_00619210();

    // Clamp to 52
    if (g_minQuality < 0x34) {
        g_minQuality = 0x34;
    }
    if (0x34 < g_maxQuality) {
        g_maxQuality = 0x34;
    }

    g_someFlag = 0;

    // Call a function with parameters (1,1,1)
    func_0041e4d0(1, 1, 1);

    // Clamp to 56
    if (g_minQuality < 0x38) {
        g_minQuality = 0x38;
    }
    if (0x38 < g_maxQuality) {
        g_maxQuality = 0x38;
    }

    g_someValue1 = 8;

    // Clamp to 57
    if (g_minQuality < 0x39) {
        g_minQuality = 0x39;
    }
    if (0x39 < g_maxQuality) {
        g_maxQuality = 0x39;
    }

    g_someValue2 = 0;

    // Clamp to 58
    if (g_minQuality < 0x3a) {
        g_minQuality = 0x3a;
    }
    if (0x3a < g_maxQuality) {
        g_maxQuality = 0x3a;
    }

    g_someValue3 = -1; // 0xffffffff

    // Call another initialization function
    func_00417cf0(1, 5, 6);

    // Clamp to 25
    if (g_minQuality < 0x19) {
        g_minQuality = 0x19;
    }
    if (0x19 < g_maxQuality) {
        g_maxQuality = 0x19;
    }

    g_someValue4 = 7;

    // Clamp to 24
    if (g_minQuality < 0x18) {
        g_minQuality = 0x18;
    }
    if (0x18 < g_maxQuality) {
        g_maxQuality = 0x18;
    }

    g_someValue5 = 0;

    // Clamp to 15
    if (g_minQuality < 0xf) {
        g_minQuality = 0xf;
    }
    if (0xf < g_maxQuality) {
        g_maxQuality = 0xf;
    }

    g_someValue6 = 0;

    // Clamp to 27 (note: condition uses 0x1a, but assignment is 0x1b, likely a bug in the original)
    if (g_minQuality < 0x1b) {
        g_minQuality = 0x1b;
    }
    if (0x1a < g_maxQuality) {
        g_maxQuality = 0x1b;
    }

    g_someValue7 = 0;

    // Clamp to 7
    if (g_minQuality < 7) {
        g_minQuality = 7;
    }
    if (7 < g_maxQuality) {
        g_maxQuality = 7;
    }

    g_someValue8 = 1;

    // Clamp to 23
    if (g_minQuality < 0x17) {
        g_minQuality = 0x17;
    }
    if (0x17 < g_maxQuality) {
        g_maxQuality = 0x17;
    }

    g_someValue9 = 4;

    // Clamp to 14
    if (g_minQuality < 0xe) {
        g_minQuality = 0xe;
    }
    g_someValue10 = 1;
    g_anotherByte = 1;
    if (0xe < g_maxQuality) {
        g_maxQuality = 0xe;
    }

    return;
}