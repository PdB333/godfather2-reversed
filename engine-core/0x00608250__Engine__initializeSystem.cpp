// FUNC_NAME: Engine::initializeSystem
int Engine::initializeSystem(void* initContext)
{
    int loadResult;

    // Pre-initialization step (e.g., allocate memory, setup globals)
    preInit(initContext);                                                      // FUN_00607e10

    // Load engine configuration from static data block (e.g., config struct)
    loadResult = g_pEngineConfigManager->loadConfig(&g_sEngineConfig);         // vtable+0x40

    // Determine if the system should be marked ready
    // Either g_bExternallyReady is already set, OR we reset g_bSystemReady and check a flag
    if (g_bExternallyReady != 0 ||
        (g_bSystemReady = 0, (g_engineStateFlags & 2) == 0))
    {
        g_bSystemReady = 1;
    }

    // If config loading failed, abort initialization
    if (loadResult < 0)
    {
        return 0;
    }

    // Apply loaded configuration (e.g., set engine parameters)
    if (g_pEngineConfigManager != nullptr)
    {
        g_pEngineConfigManager->applyConfig();                                 // vtable+0x14
    }

    // Post-initialization step (e.g., finalize dependent systems)
    postInit(initContext);                                                     // FUN_006080a0

    return 1;
}