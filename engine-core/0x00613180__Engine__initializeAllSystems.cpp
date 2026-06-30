// FUNC_NAME: Engine::initializeAllSystems
void Engine::initializeAllSystems(void)
{
    // Allocate three global singleton objects
    allocateObject(); // unknown, likely creates manager instances
    allocateObject();
    allocateObject();

    // Initialize input device system
    InputDeviceManager::initialize();

    // Initialize controller manager
    ControllerManager::initialize();

    // Register the global singleton (e.g., g_frameworkSingleton at 0x011f6b70)
    Framework::registerGlobalSingleton(&g_frameworkSingleton);
}