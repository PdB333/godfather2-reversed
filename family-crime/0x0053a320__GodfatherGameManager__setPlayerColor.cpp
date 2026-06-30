// FUNC_NAME: GodfatherGameManager::setPlayerColor
void __fastcall GodfatherGameManager::setPlayerColor(unsigned int *param_1)
{
  // Store RGBA color components from parameter array
  _DAT_0121b8d0 = param_1[0]; // Red
  _DAT_0121b8d4 = param_1[1]; // Green
  _DAT_0121b8d8 = param_1[2]; // Blue
  _DAT_0121b8dc = param_1[3]; // Alpha

  // Check if current game state is active and player is in a specific state
  if ((DAT_012058e8 == &DAT_0121b740) && // Game state pointer check
     (((DAT_0121b754 == DAT_0121bbc0) || // Player state: normal
      (DAT_0121b754 == DAT_0121bbc4) ||  // Player state: combat
      (DAT_0121b754 == DAT_0121bbc8))))  // Player state: stealth
  {
    // Apply the color to the player's outfit/character
    FUN_0060add0(DAT_0121b754, DAT_0121bb7c, &DAT_0121b8d0);
  }
}