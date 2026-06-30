// FUNC_NAME: computeSinCosAngle
void computeSinCosAngle(float angle, float* outSinCos)
{
    // +0x00: outSinCos[0]
    // +0x04: outSinCos[1]
    // +0x08: outSinCos[2]
    // +0x0C: outSinCos[3]
    outSinCos[0] = 0.0f;
    outSinCos[1] = 0.0f;

    float rad = angle * gAngleConversionFactor; // DAT_00e2cd54 (likely degrees->radians)

    // FUN_00b99fcb and FUN_00b99e20 are likely sinf and cosf
    outSinCos[2] = sinf(rad);
    outSinCos[3] = cosf(rad);
}