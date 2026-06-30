// FUNC_NAME: GodfatherGameManager::storeValueAndCheckState
void __thiscall GodfatherGameManager::storeValueAndCheckState(int value) {
    // +0x00: m_someValue (stored from in_EAX)
    g_gameManager.m_someValue = value;

    // Check if the current game instance pointer matches a specific instance (e.g., main player)
    // DAT_012058e8 likely holds the current player/object pointer
    // DAT_0121b740 is the address of the main player/instance
    // This checks if we are in the correct context (e.g., campaign mode)
    if (g_ptrs.currentInstance == &g_mainInstance) {
        // Check game state variable (e.g., eGameState enum)
        // DAT_0121b754 is m_currentState
        // DAT_0121bbc0, etc., are constants for specific states (e.g., STATE_MENU, STATE_PLAYING, STATE_PAUSED)
        if (g_gameState.m_currentState == g_gameState.STATE_PLAYING ||
            g_gameState.m_currentState == g_gameState.STATE_PAUSED ||
            g_gameState.m_currentState == g_gameState.STATE_CUTSCENE) {
            // Check a ready flag
            // DAT_0121bb84 is m_isReady
            if (g_gameState.m_isReady != 0) {
                // Call the triggering function (e.g., processEvent, startSpecialAction)
                FUN_006063b0();
            }
        }
    }
}