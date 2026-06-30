// FUNC_NAME: StateMachine::setState
void __thiscall StateMachine::setState(int this, int stateParameter) {
    *(int*)(this + 0x18) = stateParameter;        // +0x18: parameter for the state
    *(char*)(this + 0x14) = 2;                    // +0x14: sub-state (probably animation/action phase)
    *(int*)(this + 0x10) = 9;                     // +0x10: main state identifier
}