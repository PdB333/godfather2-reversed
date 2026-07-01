// FUNC_NAME: StateMachine::handleStateTransition
void __thiscall StateMachine::handleStateTransition(int* stateId) {
    char isActive;

    // Compare incoming state with current state at +0x158
    if (*stateId != *(int*)(this + 0x158)) {
        // If state matches target state at +0x160
        if (*stateId == *(int*)(this + 0x160)) {
            isActive = isStateMachineActive(); // FUN_00481620
            if (isActive != '\0') {
                // Call virtual onEnterTargetState (vtable+0x19c)
                (*(code**)(**(int**)((char*)this - 0x3c) + 0x19c))();
                releaseState(stateId); // FUN_0046efc0
                return;
            }
            handleStateDeactivate(); // FUN_008dbda0
        }
        releaseState(stateId); // FUN_0046efc0
        return;
    }

    // State matches current state
    isActive = isStateMachineActive(); // FUN_00481620
    if (isActive != '\0') {
        // Call virtual onEnterCurrentState (vtable+0x198)
        (*(code**)(**(int**)((char*)this - 0x3c) + 0x198))();
        releaseState(stateId); // FUN_0046efc0
        return;
    }
    handleStateActivate(); // FUN_008dbbf0
    releaseState(stateId); // FUN_0046efc0
    return;
}