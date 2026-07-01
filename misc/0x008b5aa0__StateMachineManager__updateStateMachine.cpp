// FUNC_NAME: StateMachineManager::updateStateMachine

void __thiscall StateMachineManager::updateStateMachine(int thisPtr, int stateComponent)
{
    uint stateIndex;
    char isGameActive;

    isGameActive = IsGameActive();
    if (isGameActive) {
        stateIndex = *(uint *)(stateComponent + 0x10); // current state index
        if (stateIndex == 0xffffffff || stateIndex >= *(uint *)(thisPtr + 0x1b0)) {
            // Invalid or out-of-range state – allocate new one
            *(uint *)(stateComponent + 0x10) = GenerateStateID();
        } else if (stateIndex < 2) {
            // Special handling for initial states (0 and 1)
            int arrayPtr;
            if (stateIndex == 1) {
                arrayPtr = *(int *)(DAT_0112b9b4 + 0x58); // global state array for state 1
            } else {
                arrayPtr = *(int *)(DAT_0112b9b4 + 0x54); // global state array for state 0
            }
            if (arrayPtr != 0) {
                ProcessState(stateIndex, arrayPtr - 1);
            }
        }
    }
    DoUpdateState(stateComponent);
    isGameActive = IsGameActive();
    if (isGameActive) {
        if (*(byte *)(thisPtr + 0x188) & 1) { // debug flag: draw state info
            DebugDrawState(*(uint *)(stateComponent + 0x14), *(uint *)(stateComponent + 0x10));
        }
        if ((*(uint *)(thisPtr + 0x188) >> 1) & 1) { // debug flag: update state info
            DebugUpdateState(*(uint *)(stateComponent + 0x14));
        }
    }
}