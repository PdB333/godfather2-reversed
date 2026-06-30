// FUNC_NAME: ObjectStateMachine::attemptStateChange
bool __fastcall ObjectStateMachine::attemptStateChange(int thisPtr)
{
    int currentStateID = *(int *)(thisPtr + 0x480);
    int pendingStateID = *(int *)(thisPtr + 0x484);
    bool bResult = false;               // local_6
    int transitionAction;               // iVar5
    bool bCallCallback = false;          // bVar2
    int callbackArg1;                   // local_4 (actually uVar3 is callbackArg2, local_4 is callbackArg3)
    int callbackArg2;                   // uVar3
    code *callbackFunction = nullptr;    // pcVar4

    // If current and pending states differ, attempt transition
    if (pendingStateID != currentStateID) {
        // Look up transition action from global table (DAT_00e2b0a0)
        // Table layout: for each current state, there is a row of 5 ints (transition types?).
        // Index = currentStateID * 5 + pendingStateID
        transitionAction = *(int *)(&DAT_00e2b0a0 + (pendingStateID + currentStateID * 4 + currentStateID) * 4);
        if (transitionAction == 0) {
            bResult = false;            // Invalid transition
        } else {
            if (transitionAction != 8) {
                // Cache callback info for later invocation
                callbackFunction = *(code **)(thisPtr + 0x210);
                callbackArg2 = *(int *)(thisPtr + 0x27c);
                callbackArg1 = *(int *)(thisPtr + 0x278);
                bCallCallback = true;
                // Note: transitionAction is used as the final state after transition?
                if (transitionAction == 3) {
                    FUN_005dbc10();                               // Some action for state 3
                    if (*(int *)(thisPtr + 0x1fc) == 0) {
                        FUN_005dbc10();                           // Execute again
                        FUN_005e9520();                            // Additional processing
                        FUN_005e8690();                            // Another processing
                    }
                }
            }
            // Update the current state to the pending state
            *(int *)(thisPtr + 0x480) = pendingStateID;
            if (bCallCallback) {
                if (callbackFunction != nullptr) {
                    callbackFunction(callbackArg2, transitionAction, callbackArg1);
                }
                // Notify external manager of state change
                FUN_005e25a0(DAT_0122350c, callbackArg2, transitionAction);
            }
            bResult = true;             // Local_6 was set to 1 originally, but above may set to 0. Here it's set based on success.
            // Actually local_6 was set to 1 initially, but if transitionAction==0 it's set to 0.
            // The code path above sets local_6 = initial 1 (or unchanged). So returning 1 implies success.
        }
        return bResult;
    }
    // No state change needed, return success
    return true;
}