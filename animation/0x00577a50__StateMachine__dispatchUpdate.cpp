// FUNC_NAME: StateMachine::dispatchUpdate
// Address: 0x577a50
// Role: Dispatches to one of two sub-update functions based on state flag.
// Checks that both the state machine's internal pointer (+0x38) and the
// owner's pointer (+0xb4) are non-null, then decides between two update paths.

void __thiscall StateMachine::dispatchUpdate(int owner) {
    // +0x38: pointer to animation state machine or active state
    // +0x3c: state type/flag (0 = path A, non-zero = path B)
    // owner+0xb4: pointer to a movement/action component
    if (*(int *)(this + 0x38) != 0 && *(int *)(owner + 0xb4) != 0) {
        if (*(int *)(this + 0x3c) == 0) {
            // Path A: likely ground or idle state update
            FUN_005764e0(owner);
        } else {
            // Path B: likely aerial or active state update
            FUN_00574bd0(owner);
        }
    }
}