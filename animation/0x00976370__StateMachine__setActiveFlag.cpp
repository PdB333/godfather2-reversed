// FUNC_NAME: StateMachine::setActiveFlag
void __thiscall StateMachine::setActiveFlag(int this, char param_2) {
    // this + 0x68 points to a sub-component (likely a state machine or behavior)
    // at that sub-component + 0x104 is a byte flag (e.g., bEnabled / bActive)
    *(char *)(*(int *)(this + 0x68) + 0x104) = param_2;
}