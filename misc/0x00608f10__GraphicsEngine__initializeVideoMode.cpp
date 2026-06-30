// FUNC_NAME: GraphicsEngine::initializeVideoMode
void GraphicsEngine::initializeVideoMode(void)
{
    // Read current resolution from global settings
    // +0x0: screen width (DAT_0120587c)
    // +0x4: screen height (DAT_01205880)
    uint32_t screenWidth = DAT_0120587c;
    uint32_t screenHeight = DAT_01205880;

    // Store width and height as volatile copies for rendering
    DAT_01205768 = screenWidth; // display width copy
    DAT_0120576c = screenHeight; // display height copy

    // Call internal video initialization
    FUN_006078c0();

    // Create primary framebuffer (depth 3, format 0x210098 = D3DFMT_A8R8G8B8)
    DAT_012058a4 = FUN_00606c80(3, 0x210098, screenWidth, screenHeight, 1, 0xffffffff);

    // Create Z-buffer (depth 26 = D3DFMT_D24S8 shadow depth stencil, same size)
    DAT_012058a8 = FUN_00606c80(0x1a, 0x210098, screenWidth, screenHeight, 1, 0xffffffff);

    // Create alternate Z-buffer at 1024x1024 for shadow maps
    DAT_012058ac = FUN_00606c80(0x1a, 0x210098, 0x400, 0x400, 1, 0xffffffff);

    // Set primary framebuffer as active render target
    DAT_0120589c = DAT_012058a4;

    // Initialize render state and clear screen
    FUN_0060dcb0(); // Reset render states

    // Set viewport (x=0, y=0, width=0, height=0, minZ=1.0, maxZ=0 = backbuffer clear)
    FUN_00609730(0, 0, 0, 0, 0x3f800000, 0);

    // Present with vsync enabled (parameter 0x31 = 49 frames, ~30fps cap)
    FUN_00609810(0x31);

    // Flip display buffers (backBuffer=1, frontBuffer=0)
    FUN_0060d8b0(1, 0);

    // Present again for clean start
    FUN_00609810(0x31);

    return;
}