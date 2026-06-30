// FUNC_NAME: Application::init
int Application::init() {
    // Call global engine initialization (0x004dd960)
    initEngineGlobals();
    // Call member-specific initialization (0x004ddc60)
    initLocalData();
    return 0; // success
}