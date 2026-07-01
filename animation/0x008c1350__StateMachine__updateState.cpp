// FUNC_NAME: StateMachine::updateState
void StateMachine::updateState()
{
    // Get the current state object pointer from the state machine
    int* stateObj = reinterpret_cast<int*>(FUN_008c12a0(this)); // returns some internal state object
    if (stateObj != nullptr) {
        // Check if current state is not the finished/terminal state (7)
        if (stateObj[1] != 7) { // +0x04: current state ID
            // Notify that we are starting a transition (arg = 1)
            FUN_008c8a80(1);
            // Re-check after notification; if still not terminal, force transition
            if (stateObj[1] != 7) {
                // Disable current action (arg = 0)
                FUN_008c80d0(0);
                // Set state to terminal state 7 with arg 0
                FUN_008c8a20(7, 0);
            }
        }
    }
}