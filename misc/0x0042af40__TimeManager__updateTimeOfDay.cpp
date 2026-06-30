// FUNC_NAME: TimeManager::updateTimeOfDay

void __thiscall TimeManager::updateTimeOfDay(int this, int unkParam)
{
    // Global variables for time and lighting settings
    static int g_currentTime;             // +0x0110b874 (last set time)
    static int g_sunriseMinutes;          // +0x012058d0 (sunrise minute offset, clamped 0x34-0x3b)
    static int g_sunsetMinutes;           // +0x00f15988 (sunset minute offset, clamped 0x34-0x3b)
    static int g_lightingState;           // +0x011f3ac4 (reset to 0 each frame)
    static int g_lightColorR;             // +0x011f41e8
    static int g_lightColorG;             // +0x011f41ec
    static int g_lightColorB;             // +0x011f41f0
    static int g_ambientLightEnable;      // +0x011f3aa8 (set to 1)
    static int g_fogMode;                 // +0x011f41d8 (set to 2)

    // Only update lighting if the time has changed
    if (g_currentTime != this) {
        FUN_00417920(this);  // Initialize lighting based on new time
        FUN_0042b0d0(unkParam);
        g_currentTime = this;
    }

    // Clamp sunrise time to maximum 59 minutes (within the hour)
    if (g_sunriseMinutes < 0x3b) {
        g_sunriseMinutes = 0x3b;
    }
    // Clamp sunset time to maximum 59 minutes
    if (0x3b < g_sunsetMinutes) {
        g_sunsetMinutes = 0x3b;
    }

    // Reset lighting update flag
    g_lightingState = 0;

    // Force day/night transition update
    FUN_0041e4d0(1, 1, 1);

    // Apply current light color from interpolated values
    FUN_0041e560(g_lightColorR, g_lightColorG, g_lightColorB);

    // Further clamp sunrise to at least 52 minutes
    if (g_sunriseMinutes < 0x34) {
        g_sunriseMinutes = 0x34;
    }
    // Further clamp sunset to at most 52 minutes
    if (0x34 < g_sunsetMinutes) {
        g_sunsetMinutes = 0x34;
    }

    // Enable ambient lighting and set fog mode to 2 (likely volumetric)
    g_ambientLightEnable = 1;
    g_fogMode = 2;
}