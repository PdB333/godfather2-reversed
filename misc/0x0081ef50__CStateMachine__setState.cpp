// FUNC_NAME: CStateMachine::setState
void __thiscall CStateMachine::setState(int newState, int param)
{
    // Store the state parameter (e.g., associated data)
    this->stateParam = param;          // +0x124
    // Mark state as active
    this->stateActive = 1;             // +0x120

    // Only transition if the state actually changes
    if (this->currentState != newState) {  // +0x11c
        // If there's an active resource (e.g., animation, controller), stop it
        if (this->currentResource != 0) {  // +0xf0
            this->stopCurrentState();      // FUN_004df600
        }
        // Initialize the new state (e.g., start animation, set up controller)
        this->startState(newState, true);  // FUN_0081edf0(param2,1)
        // Update current state
        this->currentState = newState;     // +0x11c
    }
}