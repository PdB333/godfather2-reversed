// FUNC_NAME: dispatchGameStateCommand
// Address: 0x00501030
// Dispatches game state commands based on an action code passed in EAX.
// Used by game state machine (callers at 0x00501210).
void dispatchGameStateCommand(uint32_t actionCode)
{
    switch (actionCode)
    {
    case 0:
    case 1:
        // No-op: do nothing
        break;

    case 2:
    case 5:
        // Handle common gameplay or UI transitions
        FUN_00b99fcb(); // likely engineMessage() or similar
        break;

    case 3:
        // Initialize or transition to a specific state (e.g., gameplay setup)
        // Uses global state pointers
        FUN_00535cd0(g_DAT_00e2b1a0, g_DAT_00e2b04c); // likely setState(GlobalA, GlobalB)
        break;

    case 4:
        // Cleanup or shutdown action
        FUN_004e41b0(); // likely cleanupCurrentState()
        break;

    default:
        // Unknown action code, ignore
        break;
    }
}