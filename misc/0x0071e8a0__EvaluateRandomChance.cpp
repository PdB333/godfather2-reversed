// FUNC_NAME: EvaluateRandomChance
// Function address: 0x0071e8a0
// Role: Determines outcome based on difficulty mode, a base flag, and a pseudo-random float from a circular buffer.
//       The function uses a global random index and a threshold to decide between two result sets.
//       Results: outResult (uint) and outType (uint) are set based on conditions.

// Global state (defined elsewhere):
extern uint g_randomIndex;           // DAT_012054b4 - incrementing index for random table
extern uint g_randomIndexMask;       // DAT_010c2678 - mask to keep index within table range
extern float g_randomFloatTable[];   // DAT_010c2680 - circular buffer of floats
extern float g_comparisonThreshold;  // _DAT_00d5c458 - threshold for random check

void EvaluateRandomChance(int difficultyMode, char baseFlag, uint* outResult, uint* outType)
{
    // difficultyMode: 2 seems to be a special value that always takes the low path.
    // If difficultyMode is 3, or if a random float from the table is below threshold, use high result.
    if (difficultyMode != 2)
    {
        // For difficultyMode == 3, skip the random roll and always take high path.
        // For other modes, fetch a random float from the table and compare.
        if ((difficultyMode == 3) || 
            (g_randomFloatTable[g_randomIndex & g_randomIndexMask] < g_comparisonThreshold))
        {
            // Advance the random index (only done when the random float is actually fetched)
            g_randomIndex++;
            // High result: outResult = (baseFlag != 0) + 3, outType = 5
            *outResult = (baseFlag != '\0') + 3;
            *outType = 5;
            return;
        }
        // If difficultyMode != 2 and we reach here, the condition failed (random float >= threshold)
        // But note: if difficultyMode == 3 and condition passed, we already returned.
        // The code path for difficultyMode != 2, != 3, and random >= threshold falls through.
        // However, the original decompiled code does not have an explicit else; it falls to the bottom.
        // The random index increment is only inside the if. So if we didn't enter the if, index is not advanced.
    }
    // Default / low result: outResult = (baseFlag != 0), outType = 2
    *outResult = (uint)(baseFlag != '\0');
    *outType = 2;
    return;
}