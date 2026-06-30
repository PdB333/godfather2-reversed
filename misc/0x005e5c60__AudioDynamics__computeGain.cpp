// FUNC_NAME: AudioDynamics::computeGain
static bool AudioDynamics::computeGain(float* samples, int count, float threshold, float ratio, float* outGain)
{
    // Constants from global data
    const float kInitialMin = DAT_00e2e50c;          // +0x0 (some default min value)
    const float kGainFactor = DAT_00e2afb8;          // +0x4 (scaling factor)
    const float kMaxGain = DAT_00e2b04c;             // +0x8 (upper gain limit)
    const float kMinGain = DAT_00e2cd54;             // +0xC (lower gain limit)
    const float kThresholdLow = DAT_00e44598;        // +0x10 (low threshold for activation)
    const float kCompressionKnee = DAT_00e44680;     // +0x14 (knee adjustment)
    const float kCompressionSlope = DAT_00e4472c;    // +0x18 (compression ratio parameter)

    float minVal = kInitialMin;
    uint i = 0;

    // Find the absolute minimum value in the sample array
    // Use 4-element SIMD-style unrolled loop if count > 3
    if (count > 3)
    {
        int unrolledCount = ((count - 4) >> 2) + 1;
        float* ptr = samples + 2;  // start at index 2? Actually param_1+8 means start at index 2 (since each float is 4 bytes)
        // Wait, the decompiled code uses param_1+8, which is offset 8 bytes = 2 floats in.
        // But the array starts at param_1, so ptr initially points to samples[2].
        // This suggests the function expects the array to have at least 2 elements before the actual data?
        // Actually maybe param_1 is not the array start but a structure?
        // Re-analyzing: The loop body accesses ptr[-2], ptr[-1], ptr[0], ptr[1].
        // That means it's reading 4 consecutive floats starting from ptr[-2] which is samples[0] if ptr = samples+2.
        // So the unrolled loop processes 4 samples at a time starting from index 0.
        // Updating: ptr = samples + 2, and does -2, -1, 0, 1 => indices 0,1,2,3.
        // Then increments ptr by 4 (next group from index 4,5,6,7).
        for (int j = 0; j < unrolledCount; ++j)
        {
            if (ptr[-2] < minVal) minVal = ptr[-2];
            if (ptr[-1] < minVal) minVal = ptr[-1];
            if (ptr[0] < minVal) minVal = ptr[0];
            if (ptr[1] < minVal) minVal = ptr[1];
            ptr += 4;
        }
        i = unrolledCount * 4;  // number of elements processed
    }

    // Process remaining samples (0 to 3)
    for (; i < (uint)count; ++i)
    {
        float val = *(samples + i);
        if (val < minVal)
            minVal = val;
    }

    // Dynamics processing:
    // If threshold low (DAT_00e44598) is less than ratio (param_3) -> condition for activation
    if (DAT_00e44598 < ratio)
    {
        // Compute gain reduction based on difference between threshold and minVal
        minVal = (threshold - minVal) * ratio * DAT_00e2afb8;
        bool activated = true;

        // Check if the computed gain still meets the knee condition
        if (DAT_00e44598 < (float)((uint)minVal & DAT_00e44680))
        {
            if (DAT_00e4472c <= minVal)
            {
                *outGain = DAT_00e2b04c;  // output max gain
                return true;
            }
            else
            {
                float gain = DAT_00e4472c / (DAT_00e4472c - minVal);
                // Clamp between min and max gain
                if (gain < DAT_00e2cd54)
                    gain = DAT_00e2cd54;
                else if (gain > DAT_00e2b04c)
                    gain = DAT_00e2b04c;
                *outGain = gain;
            }
        }
        else
        {
            activated = false;  // No compression applied
            *outGain = DAT_00e2b1a4;  // original gain (from decompiler: fVar5 = DAT_00e2b1a4)
        }
        return activated;
    }
    else
    {
        *outGain = DAT_00e2b1a4;  // default gain
        return false;
    }
}