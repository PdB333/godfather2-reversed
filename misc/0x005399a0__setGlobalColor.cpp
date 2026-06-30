// FUNC_NAME: setGlobalColor
void __fastcall setGlobalColor(int *color) // param_1 is a pointer to 4 ints (RGBA?)
{
    // Store the color globally
    g_globalColor[0] = color[0];
    g_globalColor[1] = color[1];
    g_globalColor[2] = color[2];
    g_globalColor[3] = color[3];

    // Check if the current UI context is the static default context
    if (g_currentUIContext == &g_staticUIContext)
    {
        // If the current UI context's member at +0x14 equals the stored value at +0x70
        if (g_staticUIContext.member14 == g_staticUIContext.member70)
        {
            // Call a function to apply the color to something (e.g., a UI element)
            FUN_0060add0(g_staticUIContext.member70, g_staticUIContext.member258, &g_globalColor);
        }
        // Also check another member at +0x78
        if ((g_currentUIContext == &g_staticUIContext) && (g_staticUIContext.member14 == g_staticUIContext.member78))
        {
            FUN_0060add0(g_staticUIContext.member78, g_staticUIContext.member2A0, &g_globalColor);
        }
    }
}