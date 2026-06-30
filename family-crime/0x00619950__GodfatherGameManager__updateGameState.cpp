// FUNC_NAME: GodfatherGameManager::updateGameState
// Address: 0x00619950
void GodfatherGameManager::updateGameState()
{
    // Store the EAX register value (likely an object pointer) into a global context variable
    // _DAT_01127808
    g_currentContext = (void*)in_EAX;

    // Check if the game manager's state table pointer matches the expected singleton address
    // DAT_012058e8 == &PTR_PTR_01127760
    if (g_stateTablePtr == &g_singletonStateTable)
    {
        // Branch based on current state (DAT_01127774)
        if (g_currentState == g_stateReady)       // DAT_01127878
        {
            // If initialization flag is set (DAT_01127848 != 0), process ready state
            if (g_initializationFlag != 0)
            {
                // FUN_006063b0
                processReadyState();
            }
        }
        else if (g_currentState == g_stateActive) // DAT_01127884
        {
            // Process active state with current data
            // FUN_0060b2f0(g_currentState, _DAT_01127870)
            processActiveState(g_currentState, g_currentData);
        }
    }
}