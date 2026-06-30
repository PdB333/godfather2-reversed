// FUNC_NAME: StateMachine::handleEvent
void __thiscall StateMachine::handleEvent(int thisPtr, int eventId) {
    // +0x58: callback function pointer (delegate)
    if (*(code **)(thisPtr + 0x58) != NULL) {
        (*(code **)(thisPtr + 0x58))(eventId);
    }

    // Global state manager singleton (vtable +0xc)
    if (DAT_012234e0 != NULL) {
        (**(code **)(*DAT_012234e0 + 0xc))();
    }

    // +0x0c: current state object pointer
    if (*(int **)(thisPtr + 0x0c) != NULL) {
        // Call virtual method (vtable+4) on the current state
        (**(code **)(**(int **)(thisPtr + 0x0c) + 4))(thisPtr);
        *(int **)(thisPtr + 0x0c) = NULL; // Clear the state pointer
    }

    // Store the event/param for later use
    *(int *)(thisPtr + 0x18) = eventId;
    // Set state active flag (byte)
    *(byte *)(thisPtr + 0x14) = 1;
    // Set new state ID to 9 (likely a specific state constant)
    *(int *)(thisPtr + 0x10) = 9;
}