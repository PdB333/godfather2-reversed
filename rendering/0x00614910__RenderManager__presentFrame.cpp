// FUNC_NAME: RenderManager::presentFrame
void RenderManager::presentFrame()
{
    // Begin frame setup: clear state, set rendering parameters
    FUN_006131d0(&DAT_011f6b30, &DAT_011f6ab0);  // likely beginFrame(backBuffer, frontBuffer?)

    // Clear/memset something twice (e.g., clear depth/stencil)
    FUN_00417560(); // first clear
    FUN_00417560(); // second clear

    // Set initial render states
    FUN_00611f70(); // e.g., setRenderStateDefaults
    FUN_00611fe0(); // e.g., setViewport

    // Copy frame constants from source to destination (64 bytes)
    // This might be a shader constant block or view-projection matrix
    g_frameConstantsDest[0] = g_frameConstantsSrc[0];
    g_frameConstantsDest[1] = g_frameConstantsSrc[1];
    // ... (16 dwords copied)
    g_frameConstantsDest[15] = g_frameConstantsSrc[15];

    // If a swap chain or back buffer exists (offset +0x3c) present it
    if ((g_renderer != 0) && (*(int *)(g_renderer + 0x3c) != 0))
    {
        FUN_0060b020(*(undefined4 *)(g_renderer + 0x10), *(int *)(g_renderer + 0x3c), &g_frameConstantsDest);
        // likely Present(device, backBuffer, dest)
    }

    // Update frame statistics / timing
    FUN_00612130(); // e.g., updateFrameStats

    // Copy another set of constants (e.g., post-processing or second pass)
    g_postProcessDest[0] = g_postProcessSrc[0];
    // ... (16 dwords copied)
    g_postProcessDest[15] = g_postProcessSrc[15];

    // Present a second buffer if available (offset +0x48)
    if ((g_renderer != 0) && (*(int *)(g_renderer + 0x48) != 0))
    {
        FUN_0060b020(*(undefined4 *)(g_renderer + 0x10), *(int *)(g_renderer + 0x48), &g_postProcessDest);
    }

    // Swap display buffers
    FUN_00612210(&DAT_011f6b70); // e.g., swapBuffers

    // End frame / flush command buffer
    FUN_00611ea0(); // e.g., endFrame / flushRendering
}