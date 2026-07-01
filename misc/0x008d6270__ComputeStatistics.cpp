// FUNC_NAME: ComputeStatistics
void ComputeStatistics(uint *output, float *samples, uint sampleCount)
{
    float fSum;
    float fSumSq;
    float fMean;
    float fVariance;
    uint loopIndex;
    uint processedCount;
    int remaining;
    float conversionOffset;

    output[0] = sampleCount;
    output[1] = 0;    // sum
    output[4] = 0;    // sum of squares

    // Unrolled loop for batches of 4 samples (when count > 3)
    if (3 < (int)sampleCount) {
        int batchCount = ((sampleCount - 4) >> 2) + 1;   // number of full batches
        processedCount = batchCount * 4;
        do {
            output[1] = (uint)(samples[0] + (float)output[1]);
            output[4] = (uint)(samples[0] * samples[0] + (float)output[4]);

            output[1] = (uint)(samples[1] + (float)output[1]);
            output[4] = (uint)(samples[1] * samples[1] + (float)output[4]);

            output[1] = (uint)(samples[2] + (float)output[1]);
            output[4] = (uint)(samples[2] * samples[2] + (float)output[4]);

            output[1] = (uint)(samples[3] + (float)output[1]);
            output[4] = (uint)(samples[3] * samples[3] + (float)output[4]);

            samples += 4;
            batchCount--;
        } while (batchCount != 0);
    } else {
        processedCount = 0;
    }

    // Process remaining samples one by one
    if (processedCount < sampleCount) {
        remaining = sampleCount - processedCount;
        do {
            output[1] = (uint)(*samples + (float)output[1]);
            fSum = *samples;
            samples++;
            remaining--;
            output[4] = (uint)(fSum * fSum + (float)output[4]);
        } while (remaining != 0);
    }

    // Compute mean = sum / count
    fSum = (float)output[1];
    float fCount = (float)(int)sampleCount;
    // Handle large unsigned values that become negative when cast to int
    if ((int)sampleCount < 0) {
        fCount += 4294967296.0f;   // 2^32 as float
    }
    output[2] = (uint)((1.0f / fCount) * fSum);   // mean

    // Store squared sum
    output[3] = (uint)(fSum * fSum);   // sum^2

    if (sampleCount == 1) {
        output[5] = 0;   // variance
        output[6] = 0;   // std deviation
        return;
    }

    // Compute sample variance = (sumSq - (sum^2)/count) / (count-1)
    float fCountMinus1 = (float)(int)(sampleCount - 1);
    if ((int)(sampleCount - 1) < 0) {
        fCountMinus1 += 4294967296.0f;
    }
    fVariance = ((float)output[4] - (1.0f / fCount) * fSum * fSum) / fCountMinus1;
    output[5] = (uint)fVariance;   // variance
    output[6] = (uint)SQRT(fVariance);   // std deviation
}