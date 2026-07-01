// FUNC_NAME: mathMod (wrapping modulo with positive result)
float mathMod(float x, float y)
{
    // Constants used in the implementation, likely from float bit manipulation.
    // DAT_00e44564 = 0x7FFFFFFF (mask to clear sign bit)
    // DAT_00e44648 = 0x4F000000  (value to help truncation, e.g., 2^23 + 2^22 for single precision)
    // _DAT_00d5780c = 0x3F800000 (float 1.0f in IEEE representation)
    // These are assumed; actual values unknown from decompiled code.
    const uint32_t kSignMask = 0x7FFFFFFF;
    const uint32_t kRoundConstant = 0x4F000000; // Example only
    const float kOne = 1.0f;

    if (x > 0.0f) {
        // Positive case: use standard fmod (via external function)
        float ratio = x / y;
        // FUN_00b9cce0 is likely fmodf() or floorf()
        float remainder = (float)FUN_00b9cce0((double)ratio);
        return remainder * y;
    }

    if (x < 0.0f) {
        // Negative case: implement modulo that yields a positive remainder
        float quotient = x / y;                // negative quotient
        // Extract the fractional part of quotient using bit-level rounding trick.
        // This isolates the integer part without branching.
        uint32_t quotBits = *(uint32_t*)&quotient;
        // Clear sign bit from quotient bits and OR with rounding constant to create a large float.
        float truncHelper = *(float*)&(kRoundConstant | (quotBits & kSignMask));
        float fractional = (quotient + truncHelper) - truncHelper;

        // Compute adjustment factor: if the truncated integer part (as float) is less than (fractional - quotient),
        // then subtract 1.0 (to adjust for negative remainder).
        float intPart = *(float*)&(quotBits & kSignMask); // reinterpret bits with sign cleared
        int adjust = (int)(intPart < (fractional - quotient)); // condition
        float adjustment = (float)(-(uint)adjust & *(uint32_t*)&kOne); // either 0 or -1.0f

        // Return final remainder = (fractional + adjustment) * y
        return (fractional - adjustment) * y; // NOTE: decompiled shows (fVar2 - adjustment) * param_2
    }

    // x == 0.0f
    return 0.0f;
}