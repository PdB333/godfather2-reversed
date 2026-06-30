// FUNC_NAME: EvaluateSequenceMapping
void EvaluateSequenceMapping(int index, int inputValueA, int inputValueB)
{
    // g_statePairs is an array of 8-byte structures at 0x011f38f0
    // Each element: pair of ints (expectedA, expectedB)
    if ((g_statePairs[index].expectedA == inputValueA) && (g_statePairs[index].expectedB == inputValueB))
    {
        // Match: produce result code 2 if index==4, else 1
        SetSequenceResult((index == 4) + 1);
        return;
    }
    // No match: update stored expectedA with inputValueA? (call to FUN_0060df60)
    UpdateSequenceState(g_statePairs[index].expectedA, inputValueA);
}