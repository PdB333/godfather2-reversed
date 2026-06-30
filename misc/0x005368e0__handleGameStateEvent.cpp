// FUNC_NAME: handleGameStateEvent
void handleGameStateEvent(void)
{
    // Store the value passed in EAX (likely an event ID or state) into global
    g_currentEvent = in_EAX;

    // Check if the current manager pointer points to a specific global instance
    if (g_someManager == &g_someManagerInstance) {
        // Compare current state with two possible states
        if (g_currentState == g_stateA) {
            // If a certain flag is set, call function to handle state A
            if (g_flag != 0) {
                FUN_006063b0(); // likely handleStateA
                return;
            }
        }
        else if (g_currentState == g_stateB) {
            // Call function with state and additional data
            FUN_0060b2f0(g_currentState, g_stateBData); // likely handleStateB
        }
    }
    // Otherwise do nothing
}