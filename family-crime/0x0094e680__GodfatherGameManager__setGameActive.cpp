// FUNC_NAME: GodfatherGameManager::setGameActive
void GodfatherGameManager::setGameActive(void) {
    int gameManager = DAT_0112a838; // pointer to GodfatherGameManager singleton
    resetGameState(0); // clear previous state
    *(byte *)(gameManager + 0xCC) = 1; // +0xCC: game active flag
}