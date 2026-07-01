// FUNC_NAME: GameInitialization::performStartup
// Function at 0x00977ea0: Simple initialization routine that calls two sub-systems setup functions.
void GameInitialization::performStartup()
{
    // Calls function at 0x00991cd0: presumably initializes core engine systems (e.g., audio, input, networking)
    initCoreSystems();
    // Calls function at 0x00976d80 with argument 0: maybe sets initial game state or clears a mode flag
    setInitialState(0);
}