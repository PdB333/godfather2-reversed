// FUNC_NAME: GameManager::setTriggerValue
// Address: 0x00536940
// Role: Stores a trigger value and invokes a secondary function if state conditions are met

extern int* g_currentStatePtr;   // DAT_012058e8 - pointer to current state instance
extern int g_stateBase;          // DAT_0121a1f0 - base state instance
extern int g_currentSubState;    // DAT_0121a204 - current sub-state identifier
extern int g_expectedSubState;   // DAT_0121a35c - expected sub-state for trigger
extern int g_conditionFlag;      // DAT_0121a330 - additional condition flag
extern int g_triggerValue;       // _DAT_0121a314 - stored trigger value

void GameManager::setTriggerValue(int param)
{
    g_triggerValue = param;
    if ((g_currentStatePtr == &g_stateBase) &&
        (g_currentSubState == g_expectedSubState) &&
        (g_conditionFlag != 0))
    {
        FUN_006063b0(); // Execute the associated action
    }
}