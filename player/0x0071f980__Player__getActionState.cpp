// FUNC_NAME: Player::getActionState
// Function at 0x0071f980: Retrieves the current action state from the player's state machine hierarchy.
// param1: this pointer to a Player object (or derived).
// Returns: -1 for invalid/unhandled states, 0 for unknown, or result from state-specific functions.
int __fastcall Player::getActionState(int this)
{
    int componentBase;
    int stateMachineBase;
    int stateId;

    // +0x4 is likely a pointer to a subcomponent (e.g., PlayerCCTVariables or Behavior)
    // Subtract 0x48 to get the containing object (e.g., Player itself)
    if (*(int*)(this + 4) == 0) {
        componentBase = 0;
    } else {
        componentBase = *(int*)(this + 4) - 0x48;
    }

    // +0x200c from that component is a pointer to the state machine (e.g., PlayerSM)
    // Subtract 0x3c to get the state machine base object
    if (componentBase == 0 || *(int*)(componentBase + 0x200c) == 0) {
        stateMachineBase = 0;
    } else {
        stateMachineBase = *(int*)(componentBase + 0x200c) - 0x3c;
    }

    if (stateMachineBase == 0) {
        return -1;
    }

    // +0x50 holds the current state ID
    stateId = *(int*)(stateMachineBase + 0x50);

    switch (stateId) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 9:
        case 10:
            return -1;
        case 6:
            return FUN_00704a00(); // State 6 handler (e.g., aiming)
        case 7:
            return FUN_00704a10(); // State 7 handler (e.g., shooting)
        case 8:
            return FUN_00704990(); // State 8 handler (e.g., driving)
        default:
            return 0;
    }
}