// FUNC_NAME: MissionManager::getObjectiveStatus
int MissionManager::getObjectiveStatus() {
    // Lock the game state mutex for thread safety (global at 0x00e2e4c8)
    lockMutex(&g_gameStateMutex);

    int stateVal1 = *(int*)(this + 0x16c);  // +0x16c: first state indicator (type/phase)
    int stateVal2 = *(int*)(this + 0x170);  // +0x170: second state indicator (sub-state)
    char busyFlag = *(char*)(this + 0x200); // +0x200: busy flag (non-zero if processing)

    // Clear the busy flag
    *(char*)(this + 0x200) = 0;

    // Unlock the mutex
    unlockMutex();

    // If the busy flag was set, return 0 (meaning "not ready" or "in progress")
    if (busyFlag != 0) {
        return 0;
    }

    // Evaluate state values
    if (stateVal1 == 1) {
        return 2;
    }

    int result = 3; // default return value
    if (stateVal2 != 2) {
        if (stateVal2 == 1 || stateVal2 == 3) {
            result = 1;
        }
        return result;
    }

    // If stateVal2 == 2, return 0
    return 0;
}