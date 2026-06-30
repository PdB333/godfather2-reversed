//FUNC_NAME: addWeightedSample
void addWeightedSample(float* sample)
{
    // Global state for weighted accumulation (used for running averages or smoothing)
    extern float s_accumulatedSum[4]; // DAT_01125230, DAT_01125234, DAT_01125238, DAT_0112523c
    extern float s_totalWeight;       // DAT_01125240
    extern float s_weightMultiplier;  // DAT_00e2b1a4 (weight factor, e.g., time delta)

    // Accumulate weighted sample components
    s_accumulatedSum[0] += s_weightMultiplier * sample[0];
    s_accumulatedSum[1] += s_weightMultiplier * sample[1];
    s_accumulatedSum[2] += s_weightMultiplier * sample[2];
    s_accumulatedSum[3] += s_weightMultiplier * sample[3];

    // Track total weight for later normalization
    s_totalWeight += s_weightMultiplier;
}