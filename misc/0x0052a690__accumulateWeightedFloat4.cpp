// FUNC_NAME: accumulateWeightedFloat4
void accumulateWeightedFloat4(const float* inValues) {
    // Accumulate weighted sum for a 4-component vector
    // Global weight factor
    extern float g_smoothWeight; // address 0x00e2b1a4
    // Global accumulated sums for each component
    extern float g_smoothSumX; // address 0x01125230
    extern float g_smoothSumY; // address 0x01125234
    extern float g_smoothSumZ; // address 0x01125238
    extern float g_smoothSumW; // address 0x0112523c
    // Total weight sum for normalization
    extern float g_smoothTotalWeight; // address 0x01125240

    g_smoothSumX += g_smoothWeight * inValues[0];
    g_smoothSumY += g_smoothWeight * inValues[1];
    g_smoothSumZ += g_smoothWeight * inValues[2];
    g_smoothSumW += g_smoothWeight * inValues[3];
    g_smoothTotalWeight += g_smoothWeight;
}