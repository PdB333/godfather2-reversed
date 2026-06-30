// FUNC_NAME: initializeVideoDefaultSettings

// Global video/gamma settings (likely part of a VideoSettings structure)
extern int32_t g_unkGamma[6]; // +0x00 (DAT_011f41dc..f4, 6 consecutive ints)
extern int32_t g_gammaBrightness; // +0x18 (DAT_011f41f8)
extern int32_t g_gammaRampFlag;   // +0x14 (DAT_011f41d8) -> boolean?
extern int32_t g_videoMinClip;    // (DAT_012058d0)
extern int32_t g_videoMaxClip;    // (DAT_00f15988)
extern int32_t g_unkFlag1;       // (DAT_011f3aa8)
extern int32_t g_unkValue;       // (DAT_0110b874)
extern int32_t g_unkGlobal;      // (DAT_011f41dc?) Already included

// Forward declarations of called functions
void setSomeVideoParameter(uint8_t param);       // FUN_0042a720
void setColorCorrectionRamp(int32_t a, int32_t b, int32_t c); // FUN_0041e4d0
void setAnotherRamp(int32_t a, int32_t b, int32_t c); // FUN_0041e560
void setBlendMode(uint8_t mode);  // FUN_00609810
void applyVideoChanges(void);     // FUN_00619210

void initializeVideoDefaultSettings(void) {
    // Set initial gamma ramp table values (likely 6 entries for 3 channels * 2 points)
    g_unkGamma[0] = 2;   // +0x00: red min?
    g_unkGamma[1] = 2;   // +0x04: green min?
    g_unkGamma[2] = 3;   // +0x08: blue min?
    g_unkGamma[3] = 4;   // +0x0C: red max?
    g_unkGamma[4] = 0xEF; // +0x10: green max?
    g_unkGamma[5] = 0xFF; // +0x14: blue max? (though gamma table more likely used elsewhere)

    // Set global parameter to 0xFF
    setSomeVideoParameter(0xFF);

    // Set color correction ramps with initial values
    setColorCorrectionRamp(2, 2, 3);
    setAnotherRamp(4, 0xEF, 0xFF);

    // Clamp global brightness/gamma values to minimum 0x34
    if (g_videoMinClip < 0x34) {
        g_videoMinClip = 0x34;
    }
    if (g_videoMaxClip > 0x34) { // max must be <= 0x34? Note reversed logic
        g_videoMaxClip = 0x34; // clamp from above
    }

    g_unkFlag1 = 1;   // Likely enables gamma correction
    g_gammaBrightness = 0; // Reset brightness offset
    g_gammaRampFlag = 1;   // Flag to apply ramp on next update

    setBlendMode(0x3F);   // Set blend mode to 0x3F (63?)
    applyVideoChanges();  // Commit/apply video settings

    g_unkValue = 0x10;   // Some video mode or flag (0x10 = 16)
}