// FUNC_NAME: initFontAtlases
// Address: 0x008f0cf0
// Initializes two font atlas textures for UI rendering. Called once at startup.
// Uses global pointers g_fontAtlasLarge and g_fontAtlasSmall.

void initFontAtlases(void)
{
    int bOk;

    // Check if large atlas needs initialization
    if (g_fontAtlasLarge == 0)
    {
        bOk = isResourceAvailable(0x54); // Check if font resource exists (0x54 = 84 bytes)
        if (bOk == 0)
        {
            g_fontAtlasLarge = 0; // Resource not available, leave null
        }
        else
        {
            // Create large font atlas (40x40 glyph cells)
            g_fontAtlasLarge = createFontAtlas(0x28, 0x28);
        }
    }

    // Check if small atlas needs initialization
    if (g_fontAtlasSmall == 0)
    {
        bOk = isResourceAvailable(0x54);
        if (bOk != 0)
        {
            // Create small font atlas (6x23 glyph cells)
            g_fontAtlasSmall = createFontAtlas(6, 0x17);
            return;
        }
        g_fontAtlasSmall = 0; // Resource not available, leave null
    }
}