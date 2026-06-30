// FUNC_NAME: applyTransformAndRound
// Role: Converts a float to an integer using a linear transform and rounding.
// Address: 0x005bc5b0
// Global constants: DAT_00e2e230 (scale), DAT_00e2cd54 (bias)
int applyTransformAndRound(float inputFloat)
{
    // round to nearest integer (assumes positive values)
    return (int)(inputFloat * *(float*)0x00e2e230 + *(float*)0x00e2cd54 + 0.5f);
}