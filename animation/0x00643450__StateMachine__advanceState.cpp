// FUNC_NAME: StateMachine::advanceState
// Address: 0x00643450
// Reconstructed from Ghidra decompilation. Uses custom calling convention: this in ECX, stateContext pointer in EAX.

void __fastcall StateMachine::advanceState(int owner, int* stateContext)
{
    // Calls base update? (FUN_00642b00)
    FUN_00642b00();

    // State switch on *stateContext (current state)
    switch (*stateContext)
    {
    case 1: // State 1
    case 3: // State 3
    {
        // Transition to state 2
        int tempState = stateContext[4];
        *stateContext = 2;
        stateContext[4] = stateContext[3];
        stateContext[3] = tempState;
        return;
    }
    case 2: // State 2
    case 4: // State 4
    {
        // Transition to state 3
        int tempState = stateContext[4];
        *stateContext = 3;
        stateContext[4] = stateContext[3];
        stateContext[3] = tempState;
        return;
    }
    case 9: // State 9
    {
        // Special processing for state 9
        FUN_00643250();
        int tempState = stateContext[4];
        stateContext[4] = stateContext[3];
        stateContext[3] = tempState;
        return;
    }
    case 10: // State 10
    case 0xB: // State 11
    {
        // Additional logic for states 10 and 11
        FUN_00642d40();

        // Check if still in state 11 and a timing condition
        if ((*stateContext == 0xB) && (*(int*)(owner + 0x34) <= stateContext[1]) && (stateContext[1] < 250))
        {
            // Decrement some counter at owner + 0x24
            *(int*)(owner + 0x24) -= 1;
        }

        // Compute new value for stateContext[1] using some random/seed function
        int seed = (stateContext[1] << 0xF) | 0x12;
        int result = FUN_006438e0(seed, *(int*)(*(int*)(owner + 0xC) + 8));
        stateContext[1] = result;

        // Set current state to 10
        *stateContext = 10;
    }
    } // end switch

    // Common swap of indices 3 and 4 (state history or prediction)
    int tempState = stateContext[4];
    stateContext[4] = stateContext[3];
    stateContext[3] = tempState;
    return;
}