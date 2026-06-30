// FUNC_NAME: Engine::initializeCoreSubsystems

void Engine::initializeCoreSubsystems(void* pFramework, void* pResourceManager, void* pRenderModule)
{
    // Store global references and initialize via vtable (offset +0x8 = Initialize)
    g_pFramework = pFramework;
    reinterpret_cast<EARS::Framework::Framework*>(pFramework)->Initialize();

    if (pResourceManager != nullptr)
    {
        g_pResourceManager = pResourceManager;
        reinterpret_cast<EARS::Framework::ResourceManager*>(pResourceManager)->Initialize();
    }

    g_pRenderModule = pRenderModule;
    reinterpret_cast<EARS::Modules::RenderModule*>(pRenderModule)->Initialize();

    // Initialize all engine subsystems in order
    InitializeMemoryManager();       // FUN_00607990
    InitializeAudioManager();        // FUN_006132c0
    InitializeGraphicsManager();     // FUN_006060a0
    InitializeCollisionManager();    // FUN_0061ad30
    InitializeNetworkManager();      // FUN_00608f10

    g_bInitialized = 0;              // DAT_01205759 - first init flag cleared

    // Setup initial color/vector structure for UI or background
    struct InitialColor {
        uint32_t val1;               // +0x00
        uint32_t val2;               // +0x04
        uint32_t zero;               // +0x08
    };
    InitialColor color = {
        g_uDefaultColor,             // DAT_00e2b1a4
        g_uDefaultColor,
        0
    };
    ApplyInitialColorState(&color);  // FUN_00609090

    InitializeGameStateManager();    // FUN_00611c20
    InitializePhysicsSystem();       // FUN_004d21e0 (Havok)

    g_bSecondFlag = 0;               // _DAT_01205474 - second init flag cleared

    InitializeInputSystem();         // FUN_004c7b40 (XInput)
    InitializeUIManager();           // FUN_00606110
}