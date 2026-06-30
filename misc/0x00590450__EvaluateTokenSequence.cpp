// FUNC_NAME: EvaluateTokenSequence
// Function address: 0x00590450
// This function processes a sequence of tokens (pointers) and accumulates a float value.
// param_2 points to a sequence descriptor: byte[1]=count, +0xc=array of pointers to tokens.
// param_3 points to a float table used by tab tokens.
// Returns accumulated sum, or 1.0 if sequence is empty.
// Called functions: FUN_00591c00 (reset accumulator?), FUN_00591160 (advance to next token?)

float __cdecl EvaluateTokenSequence(int unused, SequenceDescriptor* sequence, float* floatTable)
{
    int tokenCount;
    float currentValue;
    float accumulatedSum;
    int i;
    char** tokenArray;
    char* token;
    uint index;

    // Read signed byte at offset 1: number of tokens in sequence
    tokenCount = (int)*(char*)((int)sequence + 1);
    currentValue = 0.0f;
    accumulatedSum = 0.0f;

    // Empty sequence returns 1.0 (base value)
    if (tokenCount == 0)
    {
        return 1.0L;
    }

    // Iterate over tokens
    if (tokenCount > 0)
    {
        tokenArray = (char**)((int)sequence + 0xc); // array of pointers to token structures
        for (i = 0; i < tokenCount; i++)
        {
            token = tokenArray[i]; // each token is a pointer to a token structure

            // Check first byte of token: if it's a tab character '\t', treat as a "value" token
            if (*token == '\t')
            {
                // Extract an index from the token structure:
                // token+4 -> pointer to sub-structure; sub-structure+4 -> uint index
                index = *(uint*)(*(int*)(token + 4) + 4);

                // If the index exceeds the second element of floatTable (some limit or marker)
                if ((uint)floatTable[1] <= index) // floatTable[1] is treated as unsigned compare
                {
                    // Reset/clear some state? FUN_00591c00(&local_4) with local_4=0
                    int resetFlag = 0;
                    FUN_00591c00(&resetFlag); // likely clears or resets an accumulator
                }

                // Retrieve a float from the table at the computed index
                currentValue = *(float*)(*(int*)floatTable + index * 4);

                // If current value equals a global sentinel constant, skip accumulation
                if (currentValue != DAT_00e2b04c) // sentinel value (likely -1.0f or NaN)
                {
                    goto accumulateStep;
                }
                else
                {
                    // Value equals sentinel: still call advance but do not add to sum
                    FUN_00591160(); // advance to next token?
                }
            }
            else
            {
                // Non-tab token: operator or command
accumulateStep:
                FUN_00591160(); // advance to next token?
                // Accumulate current value (from previous iteration or from tab handling)
                currentValue = currentValue + accumulatedSum;
                accumulatedSum = currentValue;
            }
        }
    }

    return (float10)accumulatedSum;
}