// FUNC_NAME: getTimeScaleFloat
long double getTimeScaleFloat(void) {
    // 64-bit signed integer stored as two 32-bit halves:
    // low word @ 0x01205828, high word @ 0x0120582c
    uint32_t low = DAT_01205828;
    uint32_t high = DAT_0120582c;
    uint64_t raw = ((uint64_t)high << 32) | low;

    // Extract sign and magnitude (sign-magnitude representation)
    bool negative = (high & 0x80000000) != 0;
    uint64_t magnitude = raw & 0x7FFFFFFFFFFFFFFF;

    // Convert magnitude to extended precision and apply sign
    long double result;
    if (negative)
        result = -(long double)magnitude;
    else
        result = (long double)magnitude;

    // Multiply by constant scale factor @ 0x01163ec8
    result *= (long double)DAT_01163ec8;

    return result;
}