// FUNC_NAME: GameInitializer::run
void GameInitializer::run(void)
{
    // Initialize audio subsystem (likely AudioDataManager)
    AudioDataManager::initialize(); // FUN_0092b2c0

    // Initialize input subsystem (likely InputDeviceManager)
    InputDeviceManager::initialize(); // FUN_0092ca40

    // Set gameplay configuration flag (param1=4, param2=1) – possibly enable debug mode or specific feature
    GameplayDebugger::setFlag(4, 1); // FUN_00922e20

    return;
}