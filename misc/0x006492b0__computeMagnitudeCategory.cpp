// FUNC_NAME: computeMagnitudeCategory
// Function: Compute a magnitude index (0-7) for an integer.
// Used for categorizing sizes or levels (e.g., audio sample magnitude, allocation size class).
// Address: 0x006492b0
static const float kTwoToThe32 = 4294967296.0f; // 2^32, to convert negative int to unsigned float

uint computeMagnitudeCategory(int value)
{
    float fVal = (float)value;
    // If negative, convert to corresponding positive float by adding 2^32
    // This effectively treats the integer as unsigned
    if (value < 0) {
        fVal = fVal + kTwoToThe32;
    }
    // Reinterpret the float bits as unsigned integer to extract exponent
    uint bits = *reinterpret_cast<uint*>(&fVal);
    // Extract exponent bits (bits 23-30), subtract bias (127)
    // This yields floor(log2(|value|))
    uint exp = (bits >> 23) - 127;
    // Clamp exponent to minimum 6 (i.e., magnitude >= 64)
    if (exp < 6) {
        exp = 6;
    }
    // Subtract 6 to get index starting at 0
    exp -= 6;
    // Clamp to maximum 7 (i.e., for magnitudes >= 2^13 = 8192)
    if (exp > 7) {
        exp = 7;
    }
    return exp;
}