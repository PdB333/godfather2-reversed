// FUNC_NAME: scaleTimeDependentGlobals
void scaleTimeDependentGlobals(void)
{
    // Compute scaling factor: time divisor ratio
    // DAT_00e2b1a4 is likely a base time value, DAT_01125220 is a variable time step or divisor
    float scale = DAT_00e2b1a4 / DAT_01125220;

    // Scale four consecutive global floats (likely a quaternion or 4D vector) by the factor
    // These globals are at addresses: 0x01125200, 0x01125204, 0x01125208, 0x0112520C
    _DAT_01125200 *= scale;
    _DAT_01125204 *= scale;
    _DAT_01125208 *= scale;
    _DAT_0112520c *= scale;
}