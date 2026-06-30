// FUNC_NAME: GameManager::updateState
void GameManager::updateState(bool resetAll) {
    // Check if this is the global singleton instance; if not, perform cleanup first
    if (this != &g_pGameManagerSingleton) {
        Cleanup(); // FUN_00417560 - likely releases resources or resets state
    }
    InitStep1(); // FUN_00535220 - first initialization step

    if (resetAll) {
        Cleanup(); // FUN_00417560 - cleanup again before reinitialization
        InitStep2(g_bIsInitialized != false); // FUN_00535320 - pass global initialized flag
        InitStep3(); // FUN_00535290 - final initialization step
    }
}