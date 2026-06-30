// FUNC_NAME: GameStateManager::getReadyState
// Address: 0x00627fa0
// Checks if the game is in a ready state (non-zero return) and optionally returns the current game state via output parameter.
int GameStateManager::getReadyState(uint32_t* outState) {
    int ready = GameStateManager::isGameReady();     // FUN_00625a70: returns 0 if not ready
    if (ready == 0) {
        GameStateManager::logError(g_gameNotReadyString); // FUN_00627ac0: logs "Game not ready" string
    }
    if (outState != nullptr) {
        *outState = GameStateManager::getGameState(); // FUN_00625ae0: returns current game state enum
    }
    return ready;
}