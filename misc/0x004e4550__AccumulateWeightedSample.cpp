//FUNC_NAME: AccumulateWeightedSample

// Function at 0x004e4550: Accumulates a weighted sum of a 4D vector sample when its fourth component exceeds a threshold.
// Used for computing a weighted average (e.g., for smoothing camera or input).
// Input: float* sample (4 floats) passed in EAX (custom calling convention).
// Globals:
//   gThreshold (0x00e2af44) - minimum w component to include sample
//   gWeight (0x00e2b1a4) - weight multiplier for accumulation
//   gAccumX (0x01125230), gAccumY (0x01125234), gAccumZ (0x01125238), gAccumW (0x0112523c) - accumulated weighted sums
//   gAccumCount (0x01125240) - accumulated weight sum (for normalization)

void AccumulateWeightedSample(float* sample)
{
    // Only accumulate if the fourth component exceeds the threshold
    if (gThreshold < sample[3])
    {
        // Weighted accumulation of each component
        gAccumX += gWeight * sample[0];
        gAccumY += gWeight * sample[1];
        gAccumZ += gWeight * sample[2];
        gAccumW += gWeight * sample[3];
        // Accumulate the weight itself for later normalization
        gAccumCount += gWeight;
    }
}