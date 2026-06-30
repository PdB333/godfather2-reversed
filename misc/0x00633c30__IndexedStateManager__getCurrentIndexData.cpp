// FUNC_NAME: IndexedStateManager::getCurrentIndexData
int* IndexedStateManager::getCurrentIndexData(int* stateObject) {
    int* managerPtr;
    int* currentState;

    // Check state type for special handling (types 5 and 7)
    if (stateObject[0] == 5 || stateObject[0] == 7) {
        managerPtr = (int*)getSingletonManager(); // FUN_00637f90
        if (*managerPtr != 0) {
            goto checkState;
        }
    } else {
        managerPtr = &g_globalState; // DAT_00e2a93c
    }

    debugLog("index"); // FUN_006336f0, likely output "index" for debugging

checkState:
    if (*managerPtr != 6) {
        return (int*)getAlternateData(); // FUN_00633cb0
    }

    // When manager's state is 6, get data from current object
    int* objectData = getObjectData(); // FUN_00633ac0
    return (int*)objectData[2]; // return value at offset +8 (2 ints)
}