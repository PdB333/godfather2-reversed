// FUNC_NAME: statsComputeMeanVarianceStdDev
void statsComputeMeanVarianceStdDev(int* output, float* data1, uint count1, float* data2, uint count2)
{
    int totalCount = count1 + count2;
    uint processedCount1 = 0;
    output[0] = totalCount;                // +0x00: total count
    output[1] = 0;                         // +0x04: sum (accumulated as int)
    output[4] = 0;                         // +0x10: sumSquares (accumulated as int)

    // Unrolled loop for first dataset (process 4 floats at a time)
    if (count1 > 3)
    {
        int loopCount = (count1 - 4 >> 2) + 1;
        processedCount1 = loopCount * 4;
        do
        {
            output[1] = (int)(data1[0] + (float)output[1]);
            output[4] = (int)(data1[0] * data1[0] + (float)output[4]);
            output[1] = (int)(data1[1] + (float)output[1]);
            output[4] = (int)(data1[1] * data1[1] + (float)output[4]);
            output[1] = (int)(data1[2] + (float)output[1]);
            output[4] = (int)(data1[2] * data1[2] + (float)output[4]);
            output[1] = (int)(data1[3] + (float)output[1]);
            output[4] = (int)(data1[3] * data1[3] + (float)output[4]);
            data1 += 4;
            loopCount--;
        } while (loopCount != 0);
    }

    // Remaining elements of first dataset
    if (processedCount1 < count1)
    {
        int remaining1 = count1 - processedCount1;
        do
        {
            output[1] = (int)(*data1 + (float)output[1]);
            float val = *data1;
            data1++;
            remaining1--;
            output[4] = (int)(val * val + (float)output[4]);
        } while (remaining1 != 0);
    }

    // Process second dataset (same pattern)
    uint processedCount2 = 0;
    if (count2 > 3)
    {
        int loopCount2 = (count2 - 4 >> 2) + 1;
        processedCount2 = loopCount2 * 4;
        do
        {
            output[1] = (int)(data2[0] + (float)output[1]);
            output[4] = (int)(data2[0] * data2[0] + (float)output[4]);
            output[1] = (int)(data2[1] + (float)output[1]);
            output[4] = (int)(data2[1] * data2[1] + (float)output[4]);
            output[1] = (int)(data2[2] + (float)output[1]);
            output[4] = (int)(data2[2] * data2[2] + (float)output[4]);
            output[1] = (int)(data2[3] + (float)output[1]);
            float* last = data2 + 3;
            data2 += 4;
            loopCount2--;
            output[4] = (int)(*last * *last + (float)output[4]);
        } while (loopCount2 != 0);
    }

    if (processedCount2 < count2)
    {
        int remaining2 = count2 - processedCount2;
        do
        {
            output[1] = (int)(*data2 + (float)output[1]);
            float val = *data2;
            data2++;
            remaining2--;
            output[4] = (int)(val * val + (float)output[4]);
        } while (remaining2 != 0);
    }

    // Compute mean, variance, stddev
    // Magic constant for int->float conversion (0x4F800000 likely)
    float invCount = 1.0f / (float)totalCount;
    float sumFloat = (float)output[1];
    output[2] = (int)(invCount * sumFloat);         // +0x08: mean (truncated)
    output[3] = (int)(sumFloat * sumFloat);          // +0x0C: sum squared (as int)

    float denom = (float)(totalCount - 1);
    float var = ((float)output[4] - invCount * sumFloat * sumFloat) / denom;
    output[5] = (int)var;                           // +0x14: variance
    output[6] = (int)sqrtf(var);                    // +0x18: standard deviation
}