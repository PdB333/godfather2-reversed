// FUNC_NAME: MathUtils::isDeltaAboveThreshold
// Address: 0x00581870
// Purpose: Checks if the absolute difference between two floats (value1 - value2) is >= a global threshold.
// Uses fast absolute value by masking the floating-point bits with 0x7FFFFFFF. 
// First argument passed in XMM0, second on stack (__fastcall?).

bool __cdecl MathUtils::isDeltaAboveThreshold(float value1, float value2)
{
    // Global threshold (float) - loaded from DAT_00e2e210.
    // Global mask (int) - likely 0x7FFFFFFF to isolate magnitude bits.
    float threshold = *(float*)0x00e2e210;
    int mask = *(int*)0x00e44680; // Expected value: 0x7FFFFFFF

    // Compute absolute difference: reinterpret subtraction result bits as int, mask, then back to float.
    float absDiff = *(float*)&(((int)(value1 - value2)) & mask);

    // Return true if absolute difference >= threshold
    return (threshold <= absDiff);
}