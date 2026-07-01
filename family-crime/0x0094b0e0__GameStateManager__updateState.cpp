// FUNC_NAME: GameStateManager::updateState
void GameStateManager::updateState() {
    int conditionResult = checkTransitionCondition(&stack0x00000004); // likely check if state change is allowed
    if (conditionResult >= 0) {
        performStateTransition(); // execute the state change
    }
}