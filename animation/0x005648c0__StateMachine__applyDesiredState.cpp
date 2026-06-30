// FUNC_NAME: StateMachine::applyDesiredState
// Address: 0x005648c0
// Role: Copies the desired state to the current state, with special handling for state 5.
// Offsets: m_currentState at +0x4, m_desiredState at +0xC
void __thiscall StateMachine::applyDesiredState(StateMachine* this) {
    // Equivalent to: this->m_currentState = this->m_desiredState;
    // The conditional appears redundant but may be a compiler optimization or intentional check.
    if (this->m_desiredState != 5) {
        this->m_currentState = this->m_desiredState;
    } else {
        this->m_currentState = 5;
    }
}