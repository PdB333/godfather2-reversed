// FUNC_NAME: GameLogic::checkConditionAndExecuteAction
void GameLogic::checkConditionAndExecuteAction(void* actionData)
{
    // Query if a precondition is met (e.g., game state, permissions, event flag)
    int conditionMet = isConditionSatisfied(this);
    if (conditionMet != 0) {
        // If condition passes, dispatch the intended action
        executeAction(actionData);
    }
}