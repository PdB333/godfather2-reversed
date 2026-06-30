// FUNC_NAME: isGameStateSeven
// Function address: 0x004df190
// Role: Returns true if the global game state equals 7 (specific game phase)
bool isGameStateSeven(void)
{
    // g_gameState (DAT_01194540) is a global integer tracking the current game phase
    // Value 7 likely corresponds to a specific state (e.g., post-loading, main menu, or gameplay)
    return g_gameState == 7;
}