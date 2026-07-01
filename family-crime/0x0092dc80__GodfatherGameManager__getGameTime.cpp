// FUNC_NAME: GodfatherGameManager::getGameTime
void GodfatherGameManager::getGameTime(int *outTime)
{
  *outTime = 0;
  if (*(int **)(DAT_012233a0 + 4) != 0) {
    // Game manager singleton exists, return game time (offset -0x1f30 from manager base)
    *outTime = **(int **)(DAT_012233a0 + 4) + -0x1f30;
    return;
  }
  *outTime = 0;
  return;
}