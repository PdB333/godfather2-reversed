// FUNC_NAME: RenderSettings::clampDefaultValues
void RenderSettings::clampDefaultValues(void)
{
    // Call initialization functions (likely system/engine startup)
    systemInit();          // FUN_00612e00
    setInitFlag(1);        // FUN_00613570(1)

    // Clamp first set of values (possibly width/dimension related)
    if (g_someRenderWidth < 0x16) {
        g_someRenderWidth = 0x16;    // 22
    }
    if (0x16 < g_someOtherRenderWidth) {
        g_someOtherRenderWidth = 0x16;
    }
    g_flagsA = 1;

    // Second clamp (smaller value)
    if (g_someRenderWidth < 0xe) {
        g_someRenderWidth = 0xe;    // 14
    }
    if (0xe < g_someOtherRenderWidth) {
        g_someOtherRenderWidth = 0xe;
    }
    g_flagsB = 1;

    // Third set of values (possibly height/dimension related)
    if (g_someRenderHeight < 0xa8) {
        g_someRenderHeight = 0xa8;   // 168
    }
    if (0xa7 < g_someOtherRenderHeight) {
        g_someOtherRenderHeight = 0xa8;
    }
    g_someMaxAnisotropy = 0xf;       // 15

    // Fourth clamp (larger value)
    if (g_someRenderHeight < 0xbe) {
        g_someRenderHeight = 0xbe;   // 190
    }
    g_someOtherMaxAnisotropy = 0xf;  // 15
    if (0xbd < g_someOtherRenderHeight) {
        g_someOtherRenderHeight = 0xbe;
    }
    // No additional flag set for the last block
    return;
}