// FUNC_NAME: StateMachine::processActionList
// Function at 0x0082e6b0 - Processes a list of actions based on current state.
// Fields: +0x04 = currentIndex (uint), +0x08 = actionList (int**), +0x0C = state (int)
// Returns param_2 unchanged (likely a status/handle).

undefined4 __thiscall StateMachine::processActionList(int thisPtr, undefined4 param_2, undefined4 context) {
    int iVar1;
    char cVar2;
    uint uVar3;
    int iVar4;
    undefined *local_80[19]; // Temporary buffer for element processing
    undefined4 local_34;
    undefined4 local_30;
    undefined4 local_2c;
    undefined4 local_28;
    int local_24[8]; // Another temporary buffer (maybe for error info)

    int state = *(int *)(thisPtr + 0xc);
    if (state == 0) {
        // Initialization state
        initStateMachine(); // FUN_008334a0
        local_80[0] = &PTR_FUN_00d7343c; // Set vtable for temporary object
        local_34 = 0;
        local_30 = 0;
        local_2c = 0;
        local_28 = 0;
        local_24[0] = 0;
        local_24[1] = 0;
        local_24[2] = _DAT_00d5780c; // Some constant
        processElement(local_80); // FUN_00824870
        local_80[0] = &PTR_FUN_00d7343c; // Reset vtable? (maybe redundant)
        if (local_24[0] != 0) {
            cleanupAndReturn(local_24); // FUN_004daf90
            return param_2;
        }
        // If local_24[0] == 0, fall through to return
    } else {
        int* actionList = *(int**)(thisPtr + 8);
        if (state == 1) {
            // First action: get the first element directly
            iVar4 = *actionList; // Dereference pointer to pointer
        } else {
            // Normal state: find index of context in list
            uVar3 = findIndexInList(context); // FUN_00824620
            if (uVar3 == 0xffffffff) {
                // Context not found, handle error
                handleError(); // FUN_008246d0
                processElement(local_80); // FUN_00824870
                local_80[0] = &PTR_FUN_00d7343c;
                if (local_24[0] == 0) {
                    return param_2;
                }
                cleanupAndReturn(local_24); // FUN_004daf90
                return param_2;
            }
            // Store the found index
            *(uint *)(thisPtr + 4) = uVar3;
            // Determine next index (wrap around)
            if (uVar3 < (uint)(state - 1)) {
                iVar4 = uVar3 + 1;
            } else {
                iVar4 = 0;
            }
            // Get the next action pointer from list
            iVar4 = *(int *)(actionList + iVar4 * 4);
            int iVar1 = *(int *)(actionList + uVar3 * 4); // Current action pointer
            // Check if the next action is valid (compare with context+4)
            cVar2 = compareElement(context, iVar4 + 4); // FUN_00835a00
            if (cVar2 != '\0') {
                iVar4 = iVar1; // Use current action instead
            }
        }
        processElement(iVar4); // FUN_00824870
    }
    return param_2;
}