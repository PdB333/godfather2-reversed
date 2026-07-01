// FUNC_NAME: initializeGameSystems
void initializeGameSystems(void)
{
    // Call engine subsystem initialization (likely audio/input/core)
    initializeEngine(); // 0x0055ba20

    // Call game-specific initialization (managers, gameplay systems)
    initializeGameSubsystems(); // 0x00878570
}