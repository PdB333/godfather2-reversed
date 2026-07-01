// FUNC_NAME: GameModeDispatcher::updateGameMode
// Function address: 0x007e49d0
// Role: Main update dispatcher based on global game mode (2-bit field).
// Called from main loop to route update to the appropriate mode's update function.
void GameModeDispatcher::updateGameMode()
{
    // If the game is shutting down or in a blocking state, skip updates
    if (isApplicationExiting())
        return;

    uint gameMode = g_gameModeMask & 3; // Global game mode mask (DAT_01205220 & 3)

    if (gameMode == 0)
    {
        updateFrontendMode();       // Main menu / frontend
    }
    else if (gameMode == 1)
    {
        updateGameplayMode();       // Ingame gameplay
    }
    else if (gameMode == 2)
    {
        updateCinematicMode();      // Cutscenes / cinematics
    }
    else if (gameMode == 3)
    {
        updateOverlayMode();        // Pause menu / overlay / debug
    }
}