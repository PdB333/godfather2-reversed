// FUNC_NAME: StateMachine::handleAction
void __thiscall StateMachine::handleAction(int* pActionId) {
    // Compare the input action ID with known global constants
    if (*pActionId == kActionStart) {
        // If current state is 2 and an active object exists, start effect
        if ((m_state == 2) && (m_pActiveObject != nullptr)) {
            startEffect(); // FUN_004cb550
        }
        // Transition to state 1
        m_state = 1;
        return;
    }

    if (*pActionId == kActionStop) {
        // If an active object exists, stop effect with parameters (0,0)
        if (m_pActiveObject != nullptr) {
            stopEffect(0, 0); // FUN_004cb4d0(0,0)
        }
        // Transition to state 2
        m_state = 2;
    }
}