// FUNC_NAME: clampAndResetSettings
// Function address: 0x0042ac10
// Role: Applies default clamping and initializes several global settings.
// Called during startup (from FUN_0042b5d0 and FUN_00431480).
// Applies two-phase bounds: first ensures g_minSetting >= 59 and g_maxSetting <= 59,
// then ensures g_minSetting >= 52 and g_maxSetting <= 52 (net: min>=59, max<=52).
// Also resets flags, calls subroutines for default color and parameter setup.

void clampAndResetSettings(void)
{
    // Call to internal reset function (sub-function 0x0042aca0)
    resetInternalState();

    // Phase 1: clamp to 59 (0x3b)
    // g_minSetting: global at 0x012058d0 - likely a minimum threshold
    if (g_minSetting < 59)
        g_minSetting = 59;
    // g_maxSetting: global at 0x00f15988 - likely a maximum threshold
    if (g_maxSetting > 59)
        g_maxSetting = 59;

    // Reset flag at 0x011f3ac4
    g_flags1 = 0;

    // Call to set default parameters (FUN_0041e4d0) with (1,1,1)
    setDefaultParameter(1, 1, 1);

    // Apply color/lighting filter using three globals (R,G,B?) (FUN_0041e560)
    // These globals at 0x011f41e8, 0x011f41ec, 0x011f41f0
    applyColorFilter(g_colorR, g_colorG, g_colorB);

    // Phase 2: clamp to 52 (0x34)
    if (g_minSetting < 52)
        g_minSetting = 52;
    if (g_maxSetting > 52)
        g_maxSetting = 52;

    // Set flags to final values
    g_flag2 = 1;          // global at 0x011f3aa8
    g_someValue = 2;      // global at 0x011f41d8
}