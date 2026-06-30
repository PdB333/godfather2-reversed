// FUNC_NAME: GraphicsSettings::setMode
void GraphicsSettings::setMode(int mode)
{
    // Global video settings variables (likely refresh rate range)
    // These may overlap in memory; treat as separate globals for clarity
    extern int g_minRefreshRate;   // DAT_012058d0
    extern int g_maxRefreshRate;   // DAT_00f15988
    extern int g_currentRefreshRate; // _DAT_011f3ac4? Actually multiple fields

    if (mode == 0)
    {
        // Mode 0: default safe mode? Clamp refresh rates to minimum 59 (0x3b)
        if (g_minRefreshRate < 0x3b)
            g_minRefreshRate = 0x3b;
        if (g_maxRefreshRate > 0x3b)
            g_maxRefreshRate = 0x3b;

        // Set a field to -1 (likely invalid or unset)
        _DAT_011f3ac4 = 0xffffffff; // +0x? Field in global settings structure

        // Apply display mode: width=1, height=1, fullscreen=1 (maybe placeholder?)
        setDisplayMode(1, 1, 1); // FUN_0041e4d0

        // Clamp to minimum 56 (0x38)
        if (g_minRefreshRate < 0x38)
            g_minRefreshRate = 0x38;
        if (g_maxRefreshRate > 0x38)
            g_maxRefreshRate = 0x38;

        _DAT_011f3ab8 = 8; // +0x? Some setting, e.g., bit depth or refresh divisor

        // Clamp to 57 (0x39)
        if (g_minRefreshRate < 0x39)
            g_minRefreshRate = 0x39;
        if (g_maxRefreshRate > 0x39)
            g_maxRefreshRate = 0x39;

        _DAT_011f3abc = 0; // +0x?

        // Clamp to 58 (0x3a)
        if (g_minRefreshRate < 0x3a)
            g_minRefreshRate = 0x3a;
        if (g_maxRefreshRate > 0x3a)
            g_maxRefreshRate = 0x3a;

        _DAT_011f3ac0 = 0xffffffff; // +0x? Another field

        // Final clamp to 52 (0x34)
        if (g_minRefreshRate < 0x34)
            g_minRefreshRate = 0x34;
        if (g_maxRefreshRate > 0x34)
            g_maxRefreshRate = 0x34;

        _DAT_011f3aa8 = 0; // +0x? Field, e.g., fullscreen flag?
        g_currentMode = mode; // DAT_011f41d8 = unaff_EDI
    }
    else if (mode == 1)
    {
        // Mode 1: apply stored settings
        setupGraphicsDevice(g_storedDeviceIndex); // DAT_011f41f4 -> FUN_0042a720
        setDisplayMode(g_storedWidth, g_storedHeight, g_storedFullscreen); // DAT_011f41dc etc.
        setResolution(g_storedResX, g_storedResY, g_storedResZ); // DAT_011f41e8 etc.

        // Ensure refresh rates are at least 52
        if (g_minRefreshRate < 0x34)
            g_minRefreshRate = 0x34;
        if (g_maxRefreshRate > 0x34)
            g_maxRefreshRate = 0x34;

        g_storedSomething = 0; // DAT_011f41f8
        _DAT_011f3aa8 = 1; // +0x?
        g_currentMode = mode;
    }
    else
    {
        // Default: unknown mode, apply safe display and stored resolution
        // Also set refresh range to at least 59
        if (g_minRefreshRate < 0x3b)
            g_minRefreshRate = 0x3b;
        if (g_maxRefreshRate > 0x3b)
            g_maxRefreshRate = 0x3b;

        _DAT_011f3ac4 = 0; // +0x?
        setDisplayMode(1, 1, 1); // Safe mode
        setResolution(g_storedResX, g_storedResY, g_storedResZ);

        // Clamp to 52
        if (g_minRefreshRate < 0x34)
            g_minRefreshRate = 0x34;
        if (g_maxRefreshRate > 0x34)
            g_maxRefreshRate = 0x34;

        _DAT_011f3aa8 = 1; // +0x?
        g_currentMode = mode;
    }
}