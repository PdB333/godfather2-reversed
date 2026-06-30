// FUNC_NAME: readProcessedDouble
/* 0x00607350 - Reads a double from two globals, extracts sign, combines with magnitude,
   then multiplies by a constant. Likely converts a stored double to a scaled float. */
// DAT_01205828 = low 32 bits of double
// DAT_0120582c = high 32 bits of double
// DAT_01163ec8 = scaling factor (float or double)
float10 readProcessedDouble(void)
{
    // Extract the 64-bit double from two 32-bit halves (little-endian assumption)
    uint32 low = DAT_01205828;                  // +0x00
    uint32 high = DAT_0120582c;                  // +0x04
    uint64 doubleBits = ((uint64)high << 32) | low;

    // Isolate the sign bit (bit 63) and clear it from magnitude
    uint64 signBit = ((uint64)(high & 0x80000000)) << 32; // only bit 63 may be set
    uint64 magnitude = doubleBits & 0x7FFFFFFFFFFFFFFF;

    // Convert sign bit to a signed integer: either 0 or -9223372036854775808
    longlong signInt = (longlong)signBit;
    // Negate the integer to get a sign contribution (heuristic: sign becomes -0.0 or +0.0? No)
    // Then add magnitude as integer and multiply by scaling factor
    float10 signContrib = -(float10)signInt;
    float10 magFloat = (float10)magnitude;
    return (signContrib + magFloat) * (float10)_DAT_01163ec8;
}