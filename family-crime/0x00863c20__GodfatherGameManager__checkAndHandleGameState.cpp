// FUNC_NAME: GodfatherGameManager::checkAndHandleGameState
void GodfatherGameManager::checkAndHandleGameState(void)

{
  // Check if the current game state pointer is valid and not equal to 0x1f30 (likely a specific state ID)
  if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
    // If the state is valid and not the "do nothing" state (0x1f30), call the handler
    FUN_00471610();
    return;
  }
  return;
}