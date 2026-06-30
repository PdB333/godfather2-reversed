// FUNC_NAME: Engine::init
void Engine::init(void *thisPtr)
{
    // Call base initialization routine
    FUN_00698ec0(thisPtr);
    // Set global initialization flag to indicate this system is ready
    g_engineInitialized = 1;
}