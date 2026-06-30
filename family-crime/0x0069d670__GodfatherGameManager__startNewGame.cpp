// FUNC_NAME: GodfatherGameManager::startNewGame
void GodfatherGameManager::startNewGame(void)
{
    // Set flag indicating a new game has started (global state)
    DAT_0112a02a = 1;
    
    // Initialize game state with default parameters (0 = new game, not load)
    FUN_0069d240(0);
    return;
}