// FUNC_NAME: GodfatherGameManager::ResetGameState

void __fastcall GodfatherGameManager::ResetGameState(GodfatherGameManager* thisPtr)
{
    // Set sub-state to 0x13 (likely a specific phase/state ID)
    thisPtr->m_subState = 0x13;
    // Reset count/flag to 0
    thisPtr->m_someCount = 0;
    // Update global game mode to 0x11 (e.g., eGameMode_Menu, eGameMode_Intro)
    g_globalGameState = 0x11;
    // If current state is not 3, transition to state 1 and enable something
    if (thisPtr->m_currentState != 3)
    {
        SetGameStateEnabled(1);   // Enables the game state system
        thisPtr->m_currentState = 1;
    }
}