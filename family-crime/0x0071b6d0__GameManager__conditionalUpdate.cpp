// FUNC_NAME: GameManager::conditionalUpdate
void GameManager::conditionalUpdate() {
    // FUN_007f7c60: check if game is paused or in a menu state
    bool isPaused = (checkPauseFlag() != 0);
    if (!isPaused) {
        // FUN_0071b5b0: perform core game state update
        updateGameState(gpGameManager); // DAT_01205228 is the global GameManager instance
    }
}