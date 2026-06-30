// FUNC_NAME: StateMachine::handleStateTransition
// Address: 0x00675200
// Function: Sets a state value and conditionally calls another function based on current state.

// Struct definition based on accessed offsets (+0x1a, +0x20)
struct StateObject {
    // ... other fields ...
    short stateFlags;      // +0x1a: current state/flag
    short nextState;       // +0x20: next state to set (written as 2)
    // ... other fields ...
};

// __fastcall: param_1 (ecx) = unused, param_2 (edx) = pointer to StateObject
short __fastcall StateMachine::handleStateTransition(int /*unused*/, StateObject* obj)
{
    short currentState = *(short*)((char*)obj + 0x1a);  // read state at +0x1a
    *(short*)((char*)obj + 0x20) = 2;                   // set state at +0x20 to 2

    if ((currentState != 0) && (currentState != 2) && (currentState == 4))
    {
        // Transition from state 4 to state 2 triggers additional processing
        return StateMachine::handleStateFour(obj);  // calls FUN_006750b0
    }

    return 0;  // no action for other state values
}