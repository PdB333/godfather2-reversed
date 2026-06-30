// FUNC_NAME: GodfatherGameManager::handleGameStateChange
void GodfatherGameManager::handleGameStateChange(void)
{
  // Switch on the game state passed in EAX (likely from a member variable or parameter)
  switch(in_EAX) {
  case 0:  // e.g., GS_None or GS_Init
  case 1:  // e.g., GS_Loading
    return;
  case 2:  // e.g., GS_MainMenu
  case 5:  // e.g., GS_Gameplay
    FUN_00b99fcb(); // likely resumeAudio or startStreaming
    return;
  case 3:  // e.g., GS_Paused
    FUN_00535cd0(DAT_00e2b1a0, DAT_00e2b04c); // likely pauseAudio(manager, flag)
    return;
  case 4:  // e.g., GS_Cutscene
    FUN_004e41b0(); // likely startCutsceneAudio
  }
  return;
}