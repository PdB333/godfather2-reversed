// FUNC_NAME: Core::processPendingActions
void Core::processPendingActions(uint8_t actionType)
{
    // DAT_01223484 is a pointer to a global singleton (likely CoreManager or similar)
    // Check if the manager exists and if its active flag (+0x0c) is set
    if ((s_pCoreManager != nullptr) && (*(int*)(s_pCoreManager + 0x0c) != 0))
    {
        // Execute the action-specific handler
        executeAction(actionType);

        // Process a list of actions with count 4 (e.g., 4 action types)
        processActionList(&s_actionHandlersTable, 4);
    }
}