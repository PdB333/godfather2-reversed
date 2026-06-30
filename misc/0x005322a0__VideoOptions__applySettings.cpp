// FUNC_NAME: VideoOptions::applySettings
void VideoOptions::applySettings(void)
{
    // Check if settings structure pointer is valid
    if (DAT_0121bcd8 != 0) {
        // Apply texture quality setting if pointer is non-null
        if (*(int *)(DAT_0121bcd8 + 4) != 0) {
            FUN_0060b020(DAT_0121bc20, *(int *)(DAT_0121bcd8 + 4), &DAT_01218d80);
        }
        // Apply shadow quality setting if pointer is non-null
        if ((DAT_0121bcd8 != 0) && (*(int *)(DAT_0121bcd8 + 8) != 0)) {
            FUN_0060b020(DAT_0121bc20, *(int *)(DAT_0121bcd8 + 8), &DAT_01218dc0);
        }
    }

    // Clamp texture quality to valid range [0x16, 0x1b]
    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }

    // Mark settings as applied
    _DAT_011f3a44 = 1;

    // Clamp shadow quality to valid range [0x16, 0x1b]
    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    _DAT_011f3a30 = 1;
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }

    return;
}