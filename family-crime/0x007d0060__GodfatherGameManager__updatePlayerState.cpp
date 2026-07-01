// FUNC_NAME: GodfatherGameManager::updatePlayerState
void GodfatherGameManager::updatePlayerState(void)
{
  undefined4 playerState;
  
  playerState = getPlayerState(0);
  setPlayerState(playerState);
  return;
}