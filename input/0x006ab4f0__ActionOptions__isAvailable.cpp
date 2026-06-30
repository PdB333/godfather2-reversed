// FUNC_NAME: ActionOptions::isAvailable
bool ActionOptions::isAvailable(void* entity) {
    int currentGameState = getCurrentGameState(); // FUN_005e3070
    return checkActionValidity(entity, currentGameState) != 0; // FUN_005e6520
}