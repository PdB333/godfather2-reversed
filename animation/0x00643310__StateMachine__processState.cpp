// FUNC_NAME: StateMachine::processState
// Address: 0x00643310
// This function is part of a state machine update loop. It performs pre-processing,
// then dispatches state-specific initialization logic, and finally runs a common update.
// The current state is stored in the first DWORD of this (offset +0x00).

void __thiscall StateMachine::processState(StateMachine* this, int unusedParam)
{
    // Pre-process step (likely frame start or state-independent setup)
    preStateProcess(); // FUN_00642b00

    // Read current state ID from object's first field
    int state = *(int*)this; // +0x00

    // State-specific enter/setup logic
    switch (state)
    {
        case 2:
        case 4:
            // No additional setup for these states
            break;

        case 3:
            enterState3(); // FUN_006424b0
            break;

        default:
            enterDefaultState(); // FUN_006432a0
            break;

        case 9:
            enterState9(); // FUN_00643250
            break;
    }

    // Common update after state-specific logic
    commonUpdate(); // FUN_00642880
}