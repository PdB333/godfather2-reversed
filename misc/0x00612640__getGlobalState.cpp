// FUNC_NAME: getGlobalState
// Function at 0x00612640: Simple getter returning a global state variable.
// The global variable at 0x012058f4 (DAT_012058f4) presumably holds a game-wide flag or state.
uint32_t getGlobalState()
{
    return g_gameStateFlag; // Replaced DAT_012058f4 with meaningful name
}