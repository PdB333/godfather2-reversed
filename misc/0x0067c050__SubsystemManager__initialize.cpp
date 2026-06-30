// FUNC_NAME: SubsystemManager::initialize
void SubsystemManager::initialize() {
    // Perform global subsystem pre-initialization (e.g., allocate pools, set up globals)
    preInit(); // 0x0067bf30

    // Attempt to retrieve the singleton instance for this subsystem
    Subsystem* instance = getInstance(); // 0x0067bfa0
    if (instance != nullptr) {
        // Instance already exists – run full initialization on it
        initInstance(instance);   // 0x0067bdb0 (with pointer)
        postInit(instance);       // 0x009c8f10 (post‑init hook)
        return;
    }

    // No instance exists yet – create default instance implicitly
    initInstance(); // 0x0067bdb0 (no argument)
}