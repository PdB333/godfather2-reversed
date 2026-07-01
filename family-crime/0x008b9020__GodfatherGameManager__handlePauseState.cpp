// FUNC_NAME: GodfatherGameManager::handlePauseState
void GodfatherGameManager::handlePauseState(void)
{
  char isPaused;
  
  isPaused = FUN_00842870(); // likely GameStateManager::isPaused() or similar
  if (isPaused != '\0') {
    FUN_00471eb0(); // likely resumeGame() or unpause()
    return;
  }
  FUN_00471db0(0); // likely pauseGame(0) or showPauseMenu(false)
  return;
}