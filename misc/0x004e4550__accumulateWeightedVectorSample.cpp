// FUNC_NAME: accumulateWeightedVectorSample
// Address: 0x004e4550
// Role: Accumulates a weighted sample (4 floats) into a global running sum if the fourth component exceeds a threshold.
// Likely used for smoothing/filtering orientation or position data.

// Global variables (addresses inferred from decompiled code)
extern float g_threshold;          // DAT_00e2af44 - minimum value for sample[3] to trigger accumulation
extern float g_weight;             // DAT_00e2b1a4 - weight multiplier for each sample component
extern float g_accumX;             // DAT_01125230
extern float g_accumY;             // DAT_01125234
extern float g_accumZ;             // DAT_01125238
extern float g_accumW;             // DAT_0112523c
extern float g_totalWeight;        // DAT_01125240 - sum of weights applied (used for normalization later)

// Function receives pointer to 4 floats in EAX (e.g., a Vector4 or Quaternion)
void accumulateWeightedVectorSample(float* sample)
{
    // Only update if the fourth component exceeds the threshold
    if (g_threshold < sample[3])
    {
        g_accumX += g_weight * sample[0];
        g_accumY += g_weight * sample[1];
        g_accumZ += g_weight * sample[2];
        g_accumW += g_weight * sample[3];
        g_totalWeight += g_weight;
    }
}