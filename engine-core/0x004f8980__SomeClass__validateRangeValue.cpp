// FUNC_NAME: SomeClass::validateRangeValue

void SomeClass::validateRangeValue(float inputValue)
{
    // this+0x24 points to a data structure with range info
    float* rangeData = *(float**)(this + 0x24);
    
    // rangeData+0x18 = minValue, rangeData+0x1c = maxValue
    float minValue = rangeData[0x18 / 4];   // offset 0x18
    float maxValue = rangeData[0x1c / 4];   // offset 0x1c

    // The following bitwise operations are typical NaN/infinity detection,
    // but the decompiler incorrectly shows a float cast after masking.
    // Likely the original code uses a uint32 reinterpretation of the float bits.
    // Constants:
    //   DAT_00e44680 = 0x7FFFFFFF  (mask sign bit)
    //   DAT_00e2e780 = 0x7F800000  (maximum normal exponent as int, then compared as float? might be reinterpreted)
    // The pattern checks if the absolute value of a float is > 0x7F800000 (i.e., NaN or Inf).
    // Because the decompiler shows a float cast, we keep it as a comment.

    if (inputValue < minValue)
    {
        // Check if minValue is NaN/inf using bitwise test
        // Equivalent to: if (((*(uint32_t*)&minValue) & 0x7FFFFFFF) > 0x7F800000)
        if (gSomeGlobal < (float)((uint32_t)minValue & gSomeMask))
        {
            return;
        }
        return;
    }

    // inputValue >= minValue
    float diff = minValue - maxValue;
    if (gSomeGlobal < (float)((uint32_t)diff & gSomeMask))
    {
        return;
    }
    return;
}