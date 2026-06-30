// FUNC_NAME: SampleSet::getMaximumValue
// Address: 0x005906a0
// Reads a signed byte at offset +0x01 of the input data pointer to determine the number of samples.
// Calls the global sample generator (FUN_00591160) repeatedly and returns the maximum sample value.
// Returns 1.0f if count is zero.

// Assuming this is a member function of an unknown class with an unused this pointer.
float __thiscall SampleSet::getMaximumValue(void* this, void* data)
{
    int sampleCount = (int)((signed char*)data)[1]; // byte at +0x01 indicates number of iterations
    float maxValue = 0.0f;

    if (sampleCount != 0)
    {
        if (sampleCount > 0)
        {
            do
            {
                float currentSample = getGlobalSample(); // callee at 0x00591160
                if (maxValue < currentSample)
                {
                    maxValue = currentSample;
                }
                sampleCount--;
            }
            while (sampleCount != 0);
        }
        // Return as double (float10 in x87)
        return (double)maxValue;
    }
    return 1.0;
}