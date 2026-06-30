// FUNC_NAME: setGameState
// Function address: 0x00697ea0
// Role: Simple setter for a global game state variable. Returns the previous state.
// The global is used to track the current game mode (e.g., menu, gameplay, cutscene).
// This pattern is common in EARS engine for state transitions.

static int gGameState = 0; // Global variable at 0x00e506ac

int setGameState(int newState)
{
    int oldState = gGameState;
    gGameState = newState;
    return oldState;
}