// FUNC_NAME: normalizeVector4
// Reconstructed C++ function for normalizing a 4D vector (likely quaternion)
// Input: const float* src (passed in EAX)
// Output: float* dst (param_1, pointer to destination)
// Uses global thresholds: g_normalizeEpsilon (DAT_00e2cbe0) and g_normalizeScale (DAT_00e2b1a4)
void __fastcall normalizeVector4(float *dst, const float *src)
{
    float magnitudeSq;
    float scale;

    magnitudeSq = src[0] * src[0] + src[1] * src[1] + src[2] * src[2] + src[3] * src[3];

    // Skip normalization if magnitude is effectively zero
    if (magnitudeSq <= g_normalizeEpsilon) // DAT_00e2cbe0 (e.g., 1e-6f)
    {
        scale = 0.0f;
    }
    else
    {
        scale = g_normalizeScale / SQRT(magnitudeSq); // DAT_00e2b1a4 (e.g., 1.0f for pure normalization)
    }

    // Write normalized/scaled vector to output
    dst[0] = src[0] * scale;
    dst[1] = src[1] * scale;
    dst[2] = src[2] * scale;
    dst[3] = src[3] * scale;
}