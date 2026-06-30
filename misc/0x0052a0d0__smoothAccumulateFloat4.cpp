// FUNC_NAME: smoothAccumulateFloat4
// Updates a running weighted sum of 4-component vectors (e.g., position or quaternion) using a global smoothing factor.
// Input pointer to float[4] in EAX (__fastcall convention with single parameter).
// The smoothing factor (DAT_00e2b1a4) is a constant weight, likely time delta or alpha.
// The accumulated sum and weight counter are maintained in global storage.
void __fastcall smoothAccumulateFloat4(float* input)
{
    // Global smoothing weight multiplier
    extern float gSmoothWeight;               // DAT_00e2b1a4
    // Four-component accumulator (e.g., position or quaternion)
    extern float gSmoothAccumulator[4];       // DAT_01125230, 0x34, 0x38, 0x3c
    // Accumulated weight counter (number of samples * weight)
    extern float gSmoothWeightCounter;        // DAT_01125240

    // Accumulate weighted sum: accumulator += weight * input
    gSmoothAccumulator[0] += gSmoothWeight * input[0];  // +0x00
    gSmoothAccumulator[1] += gSmoothWeight * input[1];  // +0x04
    gSmoothAccumulator[2] += gSmoothWeight * input[2];  // +0x08
    gSmoothAccumulator[3] += gSmoothWeight * input[3];  // +0x0c

    // Update weight counter (effectively track total accumulated weight)
    gSmoothWeightCounter += gSmoothWeight;
}