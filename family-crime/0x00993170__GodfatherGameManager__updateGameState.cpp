// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(void)
{
  // Check if the game is not paused (byte at +0x30 of global state is zero)
  // and if the game is active (DAT_0122348c != 0)
  if ((*(char *)(DAT_01129938 + 0x30) == '\0') && (DAT_0122348c != 0)) {
    // Call the main game update function
    FUN_00481340();
    return;
  }
  return;
}