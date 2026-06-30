// FUNC_NAME: initGameSystems
void initGameSystems(int param_1)
{
    int result;
    
    g_someFlag = 0;
    // Virtual call on engine singleton: set some mode (vtable offset 0x1d8)
    (**(code **)(*g_pEngine + 0x1d8))(g_pEngine, 8, &g_renderModeStruct);
    
    if (param_1 != 0) {
        g_screenWidth  = (uint)g_windowWidth;    // DAT_0120587c
        g_screenHeight = (uint)g_windowHeight;   // DAT_01205880
        g_hasWindow = 1;                          // implied flag
    }
    
    // Initialize subsystems
    initRenderSystem();
    if (param_1 != 0) {
        // Create render targets (surfaces)
        g_hPrimarySurface = createSurface(3, 0x210098, g_windowWidth, g_windowHeight, 1, -1);
        g_hBackBufferSurface = createSurface(0x1a, 0x210098, g_windowWidth, g_windowHeight, 1, -1);
        g_hPrimarySurface = g_hPrimarySurface; // redundant assignment, likely bug in original
    }
    initInputSystem(param_1);
    initAudioSystem();
    initCamera(0, 0, 0, 0, 1.0f, 0);
    initFrameTimer(0x31);
    initPhysicsSystem();
    
    result = (**(code **)(*g_pEngine + 0x44))(g_pEngine, 0, 0, 0, 0);
    if (result == -0x7789f798) {  // 0x88760A68
        g_isInitialized = 1;
    }
    
    initFrameTimer(0x31);
    memset(&g_keyboardStateBuffer, 0xFF, 0x400);
    g_mouseX = 0;
    g_mouseDeltaX = 0xFF;
    g_mouseY = 0;
    g_mouseDeltaY = 0xFF;
    memset(&g_controllerStateBuffer, 0xFF, 0x400);
    
    return;
}