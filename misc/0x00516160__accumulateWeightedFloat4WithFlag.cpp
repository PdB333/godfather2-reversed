// FUNC_NAME: accumulateWeightedFloat4WithFlag

extern float gAccumVec[4];      // +0x012066b0 (4 floats)
extern unsigned int gAccumFlags; // +0x012066c0
extern float gMaxWeight;        // +0x012066c4
extern float gWeightMultiplier; // +0x00e2b1a4

void __cdecl accumulateWeightedFloat4WithFlag(float *data)
{
    // Accumulate weighted vector components
    gAccumVec[0] += gWeightMultiplier * data[0];
    gAccumVec[1] += gWeightMultiplier * data[1];
    gAccumVec[2] += gWeightMultiplier * data[2];
    gAccumVec[3] += gWeightMultiplier * data[3];

    // Track the maximum weight and combine flags
    if (data[5] > gMaxWeight)
        gMaxWeight = data[5];

    gAccumFlags |= (unsigned int)data[4];
}