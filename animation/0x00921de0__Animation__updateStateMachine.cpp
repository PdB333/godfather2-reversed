// FUNC_NAME: Animation::updateStateMachine
void __thiscall Animation::updateStateMachine(int thisObj, int deltaTime)
{
    int stateIdx = *(int *)(thisObj + 0x58);                // +0x58: current state index (0,1,2)
    int stateDuration = *(int *)(thisObj + 0x78 + stateIdx * 4); // +0x78: array of state durations (3 slots)
    bool stateChanged = false;
    
    if (stateDuration < 1) {
        // State has no duration; free any allocated data and skip update
        int* pAlloc = (int*)(thisObj + 0xa4);                // +0xa4: pointer to per-state allocated data
        if (*pAlloc != 0) {
            deallocateData(pAlloc);                           // FUN_004daf90
            *pAlloc = 0;
        }
        goto LOG_CHECK;
    }
    
    // Advance state time by deltaTime, wrapping modulo stateDuration
    int newTime = (stateDuration + *(int *)(thisObj + 0x74) + deltaTime) % stateDuration; // +0x74: current time
    if ((newTime != *(int *)(thisObj + 0x74)) || (deltaTime == 0)) {
        *(int *)(thisObj + 0x74) = newTime;                 // Update current time
        // Dispatch per-state update
        if (stateIdx == 0) {
            updateState0();                                 // FUN_00921730
        } else if (stateIdx == 1) {
            updateState1();                                 // FUN_009218e0
        } else if (stateIdx == 2) {
            updateState2();                                 // FUN_00921680
        }
        stateChanged = true;
    }
    
LOG_CHECK:
    if (deltaTime == 0) {
        return;
    }
    
    // Logging with global debug strings
    undefined4 local_c, local_8;
    undefined1 local_4;
    if (stateChanged) {
        local_c = DAT_011301c0;  // "state changed" debug string
    } else {
        local_c = DAT_011302c0;  // "state unchanged" debug string
    }
    local_8 = 0;
    local_4 = 0;
    debugPrint(&local_c, 0);                               // FUN_00408a00
}