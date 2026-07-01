// FUNC_NAME: SomeStateMachine::handleTransition
// Address: 0x00839230
// Role: Handles state transitions for a state machine (likely player or cover state).
// Field at +0xe4 is the current state (int).
// States: 4,5,7,8. When state=4, transitions to 7 or 8 based on inputParam.
// When state=5, transitions to 0 after calling one of two helper functions.

void __thiscall SomeStateMachine::handleTransition(int inputParam)
{
    int currentState = *(int *)(this + 0xe4); // +0xe4: state field

    if (currentState == 4)
    {
        // Transition to state 7 if inputParam is zero, else state 8
        *(uint *)(this + 0xe4) = (inputParam != 0) + 7;
    }
    else if (currentState == 5)
    {
        if (inputParam == 0) // inputParam == currentState - 5 (since currentState=5)
        {
            FUN_008391f0(); // handle state 5 with input 0
            *(undefined4 *)(this + 0xe4) = 0; // reset to state 0
            return;
        }
        FUN_008391b0(); // handle state 5 with non-zero input
        *(undefined4 *)(this + 0xe4) = 0; // reset to state 0
        return;
    }
    // No action for other states
}