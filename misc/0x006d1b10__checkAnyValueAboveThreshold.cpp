// FUNC_NAME: checkAnyValueAboveThreshold
uint checkAnyValueAboveThreshold(uint* values)
{
    uint index = 0;
    do {
        // Compare threshold with masked value converted to float
        if (g_thresholdFloat < (float)(values[index] & g_maskValue)) {
            // Return 1 (true) with index ??? but actually returns 1 regardless
            return 1;
        }
        index++;
    } while ((int)index < 3);
    return 0; // No value exceeded threshold
}