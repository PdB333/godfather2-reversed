// FUNC_NAME: checkGameStateCondition
// Address: 0x0052a120
// Role: Returns true if current game state differs from expected state and a timer hasn't exceeded threshold.
int checkGameStateCondition(void)
{
    if ((g_currentGameState != g_expectedGameState) && (g_someTimer <= g_timeThreshold))
    {
        return 1;
    }
    return 0;
}