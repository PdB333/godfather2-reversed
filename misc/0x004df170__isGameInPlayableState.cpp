// FUNC_NAME: IsGameInPlayableState
bool IsGameInPlayableState()
{
    // Check if current game state is either 5 or 6 (likely "in-game" or "cutscene" etc.)
    return (DAT_01194540 == 5) || (DAT_01194540 == 6);
}