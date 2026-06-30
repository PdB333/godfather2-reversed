// FUNC_NAME: checkGameState
// Address: 0x00527e20
// This function checks a game state condition: whether a current value is within
// two thresholds and a specific flag (bit 22 of s_stateFlags) is not set.
// The logic resolves to: (s_currentValue <= s_maxValue1 && s_currentValue <= s_maxValue2) && (s_stateFlags & 0x400000) == 0
int checkGameState()
{
    // Global variables (offsets unknown, likely from .data section)
    // s_currentValue (DAT_00e2af44)
    // s_maxValue1    (DAT_01197d70)
    // s_maxValue2    (DAT_01197d74)
    // s_stateFlags   (DAT_01197d90) - bit 0x400000 is a flag for something (e.g., cutscene active, menu open)
    if ((s_currentValue <= s_maxValue1) && (s_currentValue <= s_maxValue2) &&
        ((s_stateFlags & 0x400000) == 0))
    {
        return 1;
    }
    return 0;
}