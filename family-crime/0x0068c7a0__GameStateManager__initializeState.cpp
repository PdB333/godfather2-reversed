// FUNC_NAME: GameStateManager::initializeState
// Handles initialization of a game state object (likely part of GodfatherGameManager or similar EARS system)
// Sets internal fields, global state, and a manager sub-field. Checks and resets state if needed.
void __fastcall GameStateManager::initializeState(int thisPtr)
{
    // Set substate/mode to 0x12 (18) - possibly a specific animation or game phase identifier
    *(unsigned char *)(thisPtr + 0x14) = 0x12;

    // Clear counter/flag at offset 0x18 (4 bytes)
    *(int *)(thisPtr + 0x18) = 0;

    // Global state variable (DAT_00f17964) set to 0x11 (17)
    // This likely represents a global game state or system flag
    g_globalState = 0x11;

    // Write 5 to a field at offset 0x0C of a global manager pointer (DAT_012234d8)
    // +0x0C could be a state, timer, or parameter for that manager
    *(int *)(g_managerPointer + 0x0C) = 5;

    // Invoke some initialization routine (address 0x005648c0)
    // Likely a sub-system init (e.g., audio, input, or network)
    FUN_005648c0();

    // If the current state (at this+0x10) is not 3, reset it to 0
    // This ensures the object starts in a clean state unless it is already in state 3
    if (*(int *)(thisPtr + 0x10) != 3) {
        *(int *)(thisPtr + 0x10) = 0;
    }
}