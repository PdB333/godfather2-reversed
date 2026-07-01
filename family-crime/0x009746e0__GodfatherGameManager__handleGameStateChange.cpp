// FUNC_NAME: GodfatherGameManager::handleGameStateChange
void GodfatherGameManager::handleGameStateChange(int state)
{
  switch(state) {
  case 0: // eGameState_Init
    FUN_005c3960(); // likely GameStateManager::initialize
    FUN_005c26d0(); // likely GameStateManager::setupDefaults
    return;
  case 1: // eGameState_Load
    FUN_005c3960(); // GameStateManager::initialize (re-init on load)
    FUN_005c26d0(); // GameStateManager::setupDefaults
    return;
  case 2: // eGameState_Play
    FUN_00974600(); // GodfatherGameManager::startGameplay
    return;
  case 3: // eGameState_Pause
    FUN_00974670(); // GodfatherGameManager::pauseGame
  }
  return;
}