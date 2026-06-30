// FUNC_NAME: StateMachine::checkAndChangeState
// Function address: 0x0063dc30
// This appears to be a state machine update/transition function.
// Fields at +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18 are used.
// The constant 0x11f (287) is likely a specific state identifier (e.g., eStateActive).

void __fastcall StateMachine::checkAndChangeState(int expectedState)
{
    // Use ESI as 'this' pointer (as per decompiler's unaff_ESI)
    int* this = reinterpret_cast<int*>(unaff_ESI);

    // If current state (+0x0c) does not match expected state, handle error/fallback
    if (this[3] != expectedState) { // +0x0c = this[3]
        FUN_0063dbb0(); // likely an error or state mismatch handler
        return;
    }

    // Set field at +0x08 to value at +0x04 (perhaps a timer or counter reset)
    this[2] = this[1]; // +0x08 = +0x04

    // Check if field at +0x14 is not the "standard" state (0x11f)
    if (this[5] != 0x11f) { // +0x14 = this[5]
        // Transition: copy values to prepare for new state
        this[3] = this[5]; // +0x0c = +0x14 (apply next state)
        this[4] = this[6]; // +0x10 = +0x18 (copy associated data)
        this[5] = 0x11f; // +0x14 = 0x11f (set to standard state)
        return;
    }

    // If already in standard state, call a sub-function to determine next state
    int nextState = FUN_00639c70(&this[4], param_1); // +0x10 passed as parameter
    this[3] = nextState; // +0x0c = next state
}