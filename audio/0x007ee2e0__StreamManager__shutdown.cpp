// FUNC_NAME: StreamManager::shutdown
void StreamManager::shutdown() {
    // Check if the global stream manager state is initialized
    char isInitialized = isGlobalInitialized(&g_streamManagerGlobal);
    if (isInitialized == 0) {
        // If not initialized, reset the global state with a sentinel value
        resetGlobalState(&g_streamManagerGlobal, 0xffff);
    }
    // Perform per-instance cleanup
    this->cleanup();
}