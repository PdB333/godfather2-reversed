// FUNC_NAME: GameStateManager::dispatchState
int GameStateManager::dispatchState(int *context) {
    int *globalStatePtr;
    int result;

    // Check context type: 5 or 7 indicate a specific state path
    if (*context == 5 || *context == 7) {
        globalStatePtr = (int *)getCurrentStatePtr(); // FUN_00637f90
        if (*globalStatePtr != 0) {
            goto checkState;
        }
    } else {
        globalStatePtr = &g_globalState; // DAT_00e2a93c
    }
    debugPrint("index"); // FUN_006336f0

checkState:
    if (*globalStatePtr != 6) {
        result = handleDefault(); // FUN_00633cb0
        return result;
    }
    // State 6: call specific handler and return field at offset 8
    handleState6(); // FUN_00633ac0
    return *(int *)(in_EAX + 8); // in_EAX is return value of handleState6
}