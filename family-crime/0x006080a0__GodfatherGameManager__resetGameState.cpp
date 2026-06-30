// FUNC_NAME: GodfatherGameManager::resetGameState

void resetGameState(char param_1)
{
    int iVar1;
    
    // Global flag indicating initialisation state (e.g. DAT_01205765 -> g_bGameInitialized)
    g_bGameInitialized = 0;
    
    // Call virtual method at vtable+0x1d8 on global singleton object (DAT_01205750 -> g_pEngineSingleton)
    // This likely sets a configuration or resource path (params: 8, &DAT_01205754 -> some global string)
    (*(code **)(*(int*)g_pEngineSingleton + 0x1d8))(g_pEngineSingleton, 8, &DAT_01205754);
    
    if (param_1 != '\0') {
        // If param_1 is true, save current screen dimensions to globals
        g_nScreenWidth  = (uint)DAT_0120587c;   // e.g. g_nScreenWidth
        g_nScreenHeight = (uint)DAT_01205880;   // e.g. g_nScreenHeight
    }
    
    // Initialize rendering subsystem
    FUN_006078c0();  // TODO: rename - initRenderer()
    
    if (param_1 != '\0') {
        // Load two textures/surfaces (width, height from saved globals)
        // DAT_0120587c and DAT_01205880 are screen dimensions
        g_pBackbufferSurface = FUN_00606c80(3, 0x210098, DAT_0120587c, DAT_01205880, 1, -1);   // backbuffer
        g_pFrontbufferSurface = FUN_00606c80(0x1a, 0x210098, DAT_0120587c, DAT_01205880, 1, -1); // frontbuffer
        g_pMainSurface = g_pBackbufferSurface;   // e.g. g_pMainSurface
    }
    
    // Initialize audio subsystem
    FUN_00607dd0(param_1);  // TODO: rename - initAudio()
    
    // Initialize input subsystem
    FUN_0060dcb0();  // TODO: rename - initInput()
    
    // Set clear color to 0x3f800000 (floating point 1.0f for RGBA?)
    FUN_00609730(0, 0, 0, 0, 0x3f800000, 0);  // TODO: rename - setClearColor()
    
    // Set some global state (0x31)
    FUN_00609810(0x31);  // TODO: rename - setGlobalState()
    
    // Initialize network / other systems
    FUN_00608dc0();  // TODO: rename - initNetwork()
    
    // Query platform identity
    iVar1 = (*(code **)(*(int*)g_pEngineSingleton + 0x44))(g_pEngineSingleton, 0, 0, 0, 0);
    if (iVar1 == -0x7789f798) {   // 0x88766868 - likely a magic number for "RETAIL" or specific platform
        g_bRetailBuild = 1;   // e.g. g_bIsRetail
    }
    
    // Set state again (possibly flush)
    FUN_00609810(0x31);
    
    // Clear input arrays (0x400 bytes each)
    _memset(&g_anInputArray1, -1, 0x400);   // e.g. g_anControllerKeyState
    g_nLastInputDevice1 = 0;   // e.g. g_nActiveController
    g_nLastButton1 = 0xff;
    g_nLastInputDevice2 = 0;
    g_nLastButton2 = 0xff;
    _memset(&g_anInputArray2, -1, 0x400);
    
    return;
}