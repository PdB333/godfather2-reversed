// FUNC_NAME: PlayerSM::transitionToState
void __thiscall PlayerSM::transitionToState(int expectedState, int param)
{
    // +0x0c: m_currentState
    // +0x04: m_previousState
    // +0x08: m_lastState
    // +0x14: m_targetState (state to transition to; 0x11f = STATE_IDLE)
    // +0x10: m_nextState (used as argument for state action)
    // +0x18: m_storedState (fallback state)

    if (m_currentState != expectedState) {
        // State mismatch, abort
        FUN_0063dbb0();
        return;
    }

    m_lastState = m_previousState;

    if (m_targetState != 0x11f) {
        // Normal state transition: move target to current, store fallback, set idle
        m_currentState = m_targetState;
        m_nextState = m_storedState;
        m_targetState = 0x11f;  // STATE_IDLE
    } else {
        // Already idle, process next state via an action function
        uVar1 = FUN_00639c70(&m_nextState, param);
        m_currentState = uVar1;
    }
}