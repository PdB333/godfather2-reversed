// FUNC_NAME: applyVideoSettings
// Function address: 0x0060e970
// Role: Apply video/display settings from global variables to the engine's video configuration function.
// Global variables:
//   0x0120587c - g_resolutionWidth (int)
//   0x01205880 - g_resolutionHeight (int)
//   0x01205760 - g_refreshRate (int)
//   0x0120587f - g_fullscreenFlag (byte) - compared to '\0', argument is true when flag is 0 (inverted)
//   0x00f15a39 - g_gammaValue (float) - inferred
void applyVideoSettings(void)
{
    // Call engine configuration function with parameters from global variables.
    // Fullscreen argument is inverted: true when g_fullscreenFlag is 0.
    FUN_00607790(*(int*)0x0120587c,       // width
                 *(int*)0x01205880,       // height
                 *(int*)0x01205760,       // refresh rate
                 (*(char*)0x0120587f == 0), // fullscreen (inverted)
                 *(float*)0x00f15a39);    // gamma
    return;
}