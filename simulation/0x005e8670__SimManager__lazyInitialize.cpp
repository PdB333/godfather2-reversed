// FUNC_NAME: SimManager::lazyInitialize
void SimManager::lazyInitialize(void) {
    // Check if already initialized (flag at +0x490)
    if (!m_bInitialized) {
        // Perform one-time initialization (FUN_005e8300)
        performInit();
        m_bInitialized = true; // +0x490
    }
}