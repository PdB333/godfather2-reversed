// FUNC_NAME: GameplayDebugger::updateDebugDisplay
void GameplayDebugger::updateDebugDisplay(void *param_1, void *param_2)
{
  char isDebugEnabled;
  
  isDebugEnabled = InputManager::isDebugModeEnabled(); // FUN_00481620
  if (isDebugEnabled != '\0') {
    GameplayDebugger::drawDebugOverlay(); // FUN_007a8ca0
  }
  isDebugEnabled = InputManager::isDebugModeEnabled(); // FUN_00481620
  if (isDebugEnabled != '\0') {
    isDebugEnabled = GameplayDebugger::isMenuActive(); // FUN_0089c630
    if (isDebugEnabled == '\0') {
      GameplayDebugger::processDebugInput(param_2); // FUN_0094e280 - param_2 likely input event
    }
  }
  return;
}