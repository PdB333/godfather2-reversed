// FUNC_NAME: GraphicsDevice::initializeRenderTargets

void GraphicsDevice::initializeRenderTargets()
{
    // Copy screen dimensions from global config globals
    g_screenWidth = g_originalScreenWidth;     // +0x0? DAT_0120587c
    g_screenHeight = g_originalScreenHeight;    // +0x0? DAT_01205880

    // Clear current render target
    clearDevice();  // FUN_006078c0

    // Create main color render target (format? 0x210098, width/height from globals)
    g_mainColorTarget = createTexture(3, 0x210098, g_originalScreenWidth, g_originalScreenHeight, 1, 0xFFFFFFFF); // FUN_00606c80

    // Create depth/stencil buffer (same format, same size)
    g_depthStencilTarget = createTexture(0x1A, 0x210098, g_originalScreenWidth, g_originalScreenHeight, 1, 0xFFFFFFFF); // FUN_00606c80

    // Create an additional render target at fixed 1024x1024 resolution (for reflections? cubemap?)
    g_extraRenderTarget = createTexture(0x1A, 0x210098, 0x400, 0x400, 1, 0xFFFFFFFF); // FUN_00606c80

    // Use main color target as current render target
    g_currentRenderTarget = g_mainColorTarget;  // DAT_0120589c

    // Set viewport to full screen
    setupViewport();  // FUN_0060dcb0

    // Set world transform to identity (scale 1.0f, translation zero)
    setWorldTransform(0, 0, 0, 0, 1.0f, 0); // FUN_00609730

    // Enable depth test (render state 0x31 = D3DRS_ZENABLE maybe?)
    setRenderState(0x31);  // FUN_00609810

    // Set scissor rect to full screen (enable? arg1=1, arg2=0)
    setScissorRect(1, 0);  // FUN_0060d8b0

    return;
}