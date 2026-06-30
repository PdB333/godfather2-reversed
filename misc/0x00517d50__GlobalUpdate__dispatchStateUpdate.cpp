// FUNC_NAME: GlobalUpdate::dispatchStateUpdate
void __fastcall dispatchStateUpdate(int unkParam1, int unkParam2)
{
    // Global frame counter/time
    // g_frameCounter <= g_stateMachineTimeLimit
    // AND (g_frameCounter <= g_altTimeLimit1 OR g_frameCounter <= g_altTimeLimit2)
    if ((g_frameCounter <= g_stateMachineTimeLimit) &&
        ((g_frameCounter <= g_altTimeLimit1 || (g_frameCounter <= g_altTimeLimit2))))
    {
        // State flags (bitfield or enumeration)
        if (g_stateFlags < 5)
        {
            if (g_stateFlags == 4)
            {
                setFeedbackState(0);     // Disable feedback
                return;
            }
            else if (g_stateFlags == 0)
            {
                processInputEvent(unkParam2);  // Handle input parameter
                return;
            }
            else if (g_stateFlags == 2)
            {
                startFeedbackEffect();
                return;
            }
        }
        else
        {
            if (g_stateFlags == 8)
            {
                stopFeedbackEffect();
            }
            else if (g_stateFlags == 0x4000000)
            {
                setFeedbackState(1);     // Enable feedback
                return;
            }
        }
    }
}