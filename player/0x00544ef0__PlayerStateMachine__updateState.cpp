// FUNC_NAME: PlayerStateMachine::updateState
void __thiscall PlayerStateMachine::updateState(int* thisPtr, undefined4 param2)
{
    char activeFlag;
    char stackBuffer1[16]; // e.g., for string formatting
    char stackBuffer2[60]; // larger buffer

    // Called with param2 (likely an input or delta time)
    FUN_0046f9c0(param2);

    // Virtual call to check if the current state is active or allowed
    // vtable offset 0x19c (412 bytes) -> e.g., isStateActive()
    activeFlag = (**(code (__thiscall **)(int*))(*thisPtr + 0x19c))(thisPtr);

    if (activeFlag == '\0') {
        // State is inactive or finished
        if (thisPtr[0xba] != 0) { // offset 0x2E8 (0xba * 4) likely a state-specific flag or timer
            // Process state-specific logic
            FUN_004b59d0(param2, stackBuffer2); // e.g., readStateData
            FUN_00aa3930(stackBuffer2);          // e.g., processStateString
            FUN_009f4c70(stackBuffer1);          // e.g., updateStateVars
        }
    } else {
        // State is active – perform default/cleanup action
        FUN_0055db80(); // e.g., resetState or abortTransition
    }

    // Finalise update – virtual call at vtable offset 600 (0x258)
    // Likely something like finaliseUpdate() or triggerTransition()
    (**(code (__thiscall **)(int*))(*thisPtr + 600))(thisPtr);
    return;
}