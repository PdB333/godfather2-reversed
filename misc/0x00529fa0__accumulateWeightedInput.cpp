// FUNC_NAME: accumulateWeightedInput
void accumulateWeightedInput(float* input)
{
    // DAT_00e2b1a4: Filter coefficient (e.g., alpha for exponential smoothing)
    extern float g_filterCoefficient;
    // DAT_01125230, 34, 38, 3c: Accumulated filter state (4 floats: x,y,z,w)
    extern float g_filterAccumulator[4];

    g_filterAccumulator[0] += g_filterCoefficient * input[0];
    g_filterAccumulator[1] += g_filterCoefficient * input[1];
    g_filterAccumulator[2] += g_filterCoefficient * input[2];
    g_filterAccumulator[3] += g_filterCoefficient * input[3];
}