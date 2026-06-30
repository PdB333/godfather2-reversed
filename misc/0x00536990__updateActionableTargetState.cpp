// FUNC_NAME: updateActionableTargetState

void updateActionableTargetState(int targetId)
{
    // Store the target identifier passed in EAX (likely an entity ID or controller slot)
    g_selectedTargetId = targetId;

    // Check if the global state machine pointer points to the main instance
    if (g_actionStateMachine == &g_stateMachineInstance)
    {
        // Evaluate based on current state
        if (g_actionStateMachine->currentState == kStateIdle)   // DAT_0121a364
        {
            // If a pending interaction parameter is set, trigger immediate action
            if (g_interactionPending != 0)                       // DAT_0121a338
            {
                triggerInteraction();                           // FUN_006063b0 – no arguments
                return;
            }
        }
        else if (g_actionStateMachine->currentState == kStateTargeting)  // DAT_0121a368
        {
            // Continue targeting with the given target and additional parameter
            continueTargeting(g_actionStateMachine->currentState, g_targetParam); // FUN_0060b2f0 – two args
        }
    }
}