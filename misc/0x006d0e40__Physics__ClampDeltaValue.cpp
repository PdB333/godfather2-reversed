// FUNC_NAME: Physics::ClampDeltaValue
// Address: 0x006d0e40
// Limits the change of a variable (e.g., velocity/acceleration) so that the absolute value after applying the delta 
// does not exceed a threshold. The threshold may change based on a condition (e.g., slow-motion/UI pause).
// Uses integer bit masking on float reinterpretations to implement absolute value comparison without branches.

float __cdecl ClampDeltaValue(float currentValue, float delta)
{
    // Mask to clear sign bit for IEEE 754 single-precision (0x7FFFFFFF)
    const unsigned int absMask = *(unsigned int*)&DAT_00e44680; // Typically 0x7FFFFFFF
    float threshold = *(float*)&DAT_00e510f4;                  // Default clamping threshold
    float altThreshold = *(float*)&DAT_00e510c4;               // Alternative threshold when condition is true

    // Extract absolute values using the mask on integer representation, then compare as floats
    float absDelta = *(float*)&((*(unsigned int*)&delta) & absMask);
    float absCurrent = *(float*)&((*(unsigned int*)&currentValue) & absMask);

    if (absDelta <= absCurrent)
    {
        float newValue = currentValue - delta;
        float absNew = *(float*)&((*(unsigned int*)&newValue) & absMask);

        // Check some game condition (e.g., is in menu, cinematic, slow-mo)
        char condition = FUN_00410eb0(); // call to unknown condition function
        if (condition != 0)
        {
            threshold = altThreshold;
        }

        if (threshold < absNew)
        {
            // Scale the new value so that its magnitude becomes the threshold
            newValue = (threshold / absNew) * newValue;
        }
        return newValue + delta;
    }
    return currentValue;
}