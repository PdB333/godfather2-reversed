// FUNC_NAME: scaleGlobalMultipliers
// Address: 0x00529fd0
// Role: Scales four consecutive global float values (likely an RGBA color or vector) by a factor.
// The globals at 0x01125230, 0x01125234, 0x01125238, 0x0112523c form an array of 4 floats.
// This function multiplies each element by the input scale factor.

void scaleGlobalMultipliers(float scale)
{
    // Offsets: +0x00, +0x04, +0x08, +0x0C relative to base (0x01125230)
    gGlobalMultipliers[0] *= scale;
    gGlobalMultipliers[1] *= scale;
    gGlobalMultipliers[2] *= scale;
    gGlobalMultipliers[3] *= scale;
}