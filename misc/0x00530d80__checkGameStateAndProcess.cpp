// FUNC_NAME: checkGameStateAndProcess
void checkGameStateAndProcess(void)
{
    // Check if the current game state matches the expected state
    if (g_gameState == g_expectedState) {
        // If condition flag 1 is set, perform action
        if (g_conditionFlag1) {
            performTask();
        }
        // If condition flag 2 is set, perform action
        if (g_conditionFlag2) {
            performTask();
        }
    }
}