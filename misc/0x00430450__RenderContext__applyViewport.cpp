// FUNC_NAME: RenderContext::applyViewport
void RenderContext::applyViewport()
{
    // +0x80: stored viewport X?
    *(int *)(this + 0x80) = g_viewportX; // DAT_011f38f0

    int oldX = g_viewportX; // uVar1
    int oldY = g_viewportY; // uVar2

    // +0x39f8: some mode/state flag
    if ((*(int *)(this + 0x39f8) == 0) ||
        (g_viewportX = g_altViewportX, *(int *)(this + 0x39f8) == 3)) { // DAT_01123f10
        g_viewportX = g_altViewportY; // DAT_01123f0c
    }

    g_viewportY = 0; // DAT_011f38f4

    // Set viewport rectangle (index 0)
    setViewport(0, oldX, oldY); // FUN_00609340

    *(int *)(this + 0x24) = 0;

    anotherRenderFunction(); // FUN_0042b010

    int savedX = g_otherViewportX; // uVar4 = DAT_011f3910
    int curY = g_viewportY;        // uVar2
    int curX = g_viewportX;        // uVar1

    if ((g_platformType != 1) && (g_platformType != 2)) { // DAT_00f15a14
        g_viewportX = g_otherViewportX;
        g_viewportY = 0;

        // Call setViewport with the old values (before the if)
        setViewport(0, curX, curY); // FUN_00609340

        // Clear color and depth
        setClearColor(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f); // FUN_00609730
        clearBuffers(0xf); // GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT // FUN_00609810
        setClearColor(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // FUN_00609730

        int tempX = g_viewportX;
        int tempY = g_viewportY;
        g_viewportY = 0;
        g_viewportX = savedX;

        // Set viewport back to saved values
        setViewport(0, tempX, tempY); // FUN_00609340

        int oldOtherX = g_otherViewportX; // uVar2 = DAT_011f38fc
        int oldOtherY = g_otherViewportY; // uVar1 = DAT_011f38f8
        g_otherViewportY = savedX; // DAT_011f38f8
        g_otherViewportX = 0;    // DAT_011f38fc

        // Set another viewport rectangle (index 1)
        setViewport(1, oldOtherY, oldOtherX); // FUN_00609340
    }
}