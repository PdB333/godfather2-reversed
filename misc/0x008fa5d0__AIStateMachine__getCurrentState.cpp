// FUNC_NAME: AIStateMachine::getCurrentState

int __thiscall AIStateMachine::getCurrentState(void* this) {
    // Internal function to retrieve state data pointer (e.g., from a component or derived object)
    int* stateData = (int*)FUN_008c74d0(this);
    if (stateData != nullptr) {
        int state = *(int*)((char*)stateData + 0x50);   // +0x50: current state field
        if (state == 2) {
            return 2;   // e.g., kStateActive
        }
        if (state == 3) {
            return 1;   // e.g., kStateIdle
        }
    }
    return 0;   // e.g., kStateNone
}