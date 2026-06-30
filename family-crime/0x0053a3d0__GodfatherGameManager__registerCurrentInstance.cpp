// FUNC_NAME: GodfatherGameManager::registerCurrentInstance
void __thiscall GodfatherGameManager::registerCurrentInstance()
{
    // Store the 'this' pointer (passed in EAX by convention) into a static global singleton tracker
    // +0x0: static member g_currentInstance (DAT_0121b900)
    g_currentInstance = this;

    // Check if a global pointer (g_someBasePointer) points to a specific static variable (g_internalState)
    // If so, and if a state value (g_currentState) is one of three allowed states, and a flag (g_actionFlag) is non-zero,
    // call an internal handler function (at 0x6063b0)
    if (g_someBasePointer == &g_internalState &&
        (g_currentState == STATE_IDLE || g_currentState == STATE_RUNNING || g_currentState == STATE_FINISHED) &&
        g_actionFlag != 0)
    {
        HandleInternalTrigger();  // FUN_006063b0
    }
}