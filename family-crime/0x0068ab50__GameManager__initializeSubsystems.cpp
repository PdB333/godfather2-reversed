// FUNC_NAME: GameManager::initializeSubsystems
void GameManager::initializeSubsystems(void)
{
    // Initialize various engine subsystems
    initAudioSystem();          // FUN_0056aec0
    initNetworkSystem();        // FUN_00688af0
    initInputSystem();          // FUN_00688890
    initGraphicsSystem();       // FUN_00688a10
    // Mark subsystem initialization as complete
    g_subsystemsInitialized = 1; // DAT_012051fa = 1
    initPhysicsSystem();        // FUN_009cb050
    return;
}