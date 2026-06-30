// FUNC_NAME: StateMachine::initializeState
void __thiscall StateMachine::initializeState(int thisPtr, int newValue)
{
    // +0x10: current state ID (set to 9 - likely an initial state like "active")
    *(int *)(thisPtr + 0x10) = 9;
    // +0x14: state substep or flags (2 - e.g., "running" or "enabled")
    *(uint8_t *)(thisPtr + 0x14) = 2;
    // +0x18: target or associated data (passed in)
    *(int *)(thisPtr + 0x18) = newValue;
}