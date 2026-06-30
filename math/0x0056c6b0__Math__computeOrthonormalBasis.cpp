// FUNC_NAME: Math::computeOrthonormalBasis
void Math::computeOrthonormalBasis(float* out, const float* forward, const float* up)
{
    // Extract forward vector (in1)
    float fwdX = forward[0];
    float fwdY = forward[1];
    float fwdZ = forward[2];
    float fwdW = forward[3];  // unused but preserved in cross product

    // Extract up vector (in2)
    float upX = up[0];
    float upY = up[1];
    float upZ = up[2];
    float upW = up[3];  // unused

    // Compute right = cross(forward, up)
    float rightX = fwdY * upZ - fwdZ * upY;
    float rightY = fwdZ * upX - fwdX * upZ;
    float rightZ = fwdX * upY - fwdY * upX;
    float rightW = fwdW * upW - fwdW * upW;  // always 0

    out[0] = rightX;
    out[1] = rightY;
    out[2] = rightZ;
    out[3] = rightW;  // 0

    // Normalize right vector
    float sqLen = out[0]*out[0] + out[1]*out[1] + out[2]*out[2];
    float invLen = 0.0f;
    if (sqLen > epsilon)  // DAT_00e2cbe0
    {
        invLen = oneOverSqrtConstant / sqrtf(sqLen);  // DAT_00e2b1a4 is 1.0? Actually it's probably 1.0f constant
    }
    else
    {
        invLen = 0.0f;
    }
    out[0] *= invLen;
    out[1] *= invLen;
    out[2] *= invLen;

    // Recompute up = cross(forward, normalized right)
    float upPrimeX = out[2] * fwdY - out[1] * fwdZ;
    float upPrimeY = out[0] * fwdZ - out[2] * fwdX;
    float upPrimeZ = out[1] * fwdX - out[0] * fwdY;
    float upPrimeW = out[3] * fwdW - out[3] * fwdW;  // always 0

    out[4] = upPrimeX;
    out[5] = upPrimeY;
    out[6] = upPrimeZ;
    out[7] = upPrimeW;

    // Call floating point state function (likely flush denormals or set rounding)
    flushDenormals();  // FUN_00414aa0

    // Zero out the translation component of the third row (row 2, column 3)
    out[11] = 0.0f;
}