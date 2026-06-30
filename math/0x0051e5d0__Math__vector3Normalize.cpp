// FUNC_NAME: Math::vector3Normalize
void __fastcall Math::vector3Normalize(float *dst, float *src)
{
    // Constants from global data (likely defined elsewhere)
    // DAT_00e2cbe0: epsilon for near-zero length (e.g., 1e-6f)
    // DAT_00e2b1a4: 1.0f
    float lenSq = src[0] * src[0] + src[1] * src[1] + src[2] * src[2];
    float scale;
    if (lenSq <= DAT_00e2cbe0)
    {
        scale = 0.0f; // zero vector – no direction
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(lenSq);
    }
    dst[0] = src[0] * scale;
    dst[1] = src[1] * scale;
    dst[2] = src[2] * scale;
}