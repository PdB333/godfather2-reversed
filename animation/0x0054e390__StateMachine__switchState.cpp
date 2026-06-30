//FUNC_NAME: StateMachine::switchState
// Address: 0x0054e390
// Role: Toggles between two state pointers when current state matches one of them.
// Structure offsets:
//   +0x18: m_currentState (pointer to current state object)
//   +0x1c: m_stateA (pointer to first state)
//   +0x20: m_stateB (pointer to second state)
void __thiscall StateMachine::switchState(int param_2) {
    // If current state is already one of the two states, activate the other.
    if (m_currentState == m_stateA || m_currentState == m_stateB) {
        if (param_2 == 0) {
            processState(m_stateA);  // FUN_0054e3d0
        } else {
            processState(m_stateB);  // FUN_0054e3d0
        }
    }
}