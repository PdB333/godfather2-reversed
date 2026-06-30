// FUNC_NAME: applyScaleToVector4
// Function address: 0x0052d230
// Role: Scales a 4-component vector (likely quaternion or float4) by a ratio of two global floats.
// Used to normalize or adjust some engine parameter.

void applyScaleToVector4(void)
{
    // Obtain scaling factor from global values.
    // DAT_00e2b1a4 - numerator; DAT_01125280 - denominator
    float scale = g_scaleNumerator / g_scaleDenominator;

    // Scale each component of the vector.
    // The four globals (0x01125260, 0x01125264, 0x01125268, 0x0112526c) form a contiguous array.
    g_vector4Component0 *= scale; // +0x00
    g_vector4Component1 *= scale; // +0x04
    g_vector4Component2 *= scale; // +0x08
    g_vector4Component3 *= scale; // +0x0C
}