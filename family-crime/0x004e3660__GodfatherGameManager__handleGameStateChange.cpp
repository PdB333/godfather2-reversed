// FUNC_NAME: GodfatherGameManager::handleGameStateChange
void GodfatherGameManager::handleGameStateChange(void)
{
  int gameState = in_EAX;
  
  DAT_011946b0 = 1; // Set some global flag (likely g_gameStateChanged or similar)
  
  if (gameState == 0) { // GS_MAIN_MENU or GS_INIT
    FUN_00417db0(5, 2, 1, 1, 2); // Likely setGameState or transitionToState
    return;
  }
  if (gameState == 10) { // GS_GAMEPLAY or GS_WORLD
    FUN_00417db0(2, 2, 1, 1, 2);
    return;
  }
  if (gameState == 1) { // GS_LOADING or GS_TRANSITION
    FUN_00417db0(5, 6, 1, 2, 6);
    return;
  }
  if (gameState == 2) { // GS_PAUSED or GS_MENU
    FUN_00417db0(5);
  }
  return;
}