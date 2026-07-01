// FUNC_NAME: GameStateManager::conditionalShowPause
void GameStateManager::conditionalShowPause(void)
{
    char isActive;
    
    isActive = this->isGameActive();  // e.g., checks if not in menu/cutscene
    if (isActive != '\0') {
        this->showPauseMenu();        // e.g., opens pause overlay
    }
    return;
}