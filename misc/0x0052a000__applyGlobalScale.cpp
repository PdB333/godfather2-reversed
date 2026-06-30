// FUNC_NAME: applyGlobalScale
// Address: 0x0052a000 - Scales four consecutive global float values by a constant multiplier.
void applyGlobalScale(void)
{
    // Four consecutive global floats (likely a vector or quaternion) at 0x01125230
    // Multiplier stored at 0x00e2b05c
    gScaleValue0 = gScaleFactor * gScaleValue0;  // +0x00
    gScaleValue1 = gScaleFactor * gScaleValue1;  // +0x04
    gScaleValue2 = gScaleFactor * gScaleValue2;  // +0x08
    gScaleValue3 = gScaleFactor * gScaleValue3;  // +0x0C
}