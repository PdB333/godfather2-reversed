// FUNC_NAME: setDisplayModeConfig

// Global variables related to display configuration
extern int g_minDisplayModeIndex;
extern int g_selectedDisplayModeIndex;
extern int g_isFullscreen;
extern int g_defaultColorDepth;

// Calls an internal setup function (likely initializes display adapter)
extern void FUN_004ec7a0(); // placeholder name

// Adjusts display mode settings and outputs a color depth value
void setDisplayModeConfig(int mode, int *outColorDepth)
{
    // Clamp minimum allowed display mode index to 27 (likely a fallback)
    if (g_minDisplayModeIndex < 27)
    {
        g_minDisplayModeIndex = 27;
    }

    // Cap selected display mode index to 27 if it exceeds 26
    if (g_selectedDisplayModeIndex > 26)
    {
        g_selectedDisplayModeIndex = 27;
    }

    // Set fullscreen flag; mode 3 indicates a specific windowed/borderless state
    g_isFullscreen = (mode != 3) ? 1 : 0;

    // Perform internal setup (e.g., device creation or mode switching)
    FUN_004ec7a0();

    // Write the default color depth to the output pointer
    *outColorDepth = g_defaultColorDepth;

    // Mode 1 overrides the output to zero (e.g., force 16-bit? disable?)
    if (mode == 1)
    {
        *outColorDepth = 0;
    }
}