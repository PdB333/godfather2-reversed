// FUNC_NAME: normalizeVector4
// Function address: 0x0056afa0
// Role: Normalizes a 4-component vector (e.g., quaternion) and returns its original length.
// Input: pointer to 4 floats (x, y, z, w) in param_1
// Output: pointer to 4 floats (normalized vector) in param_2
// Returns: length of original vector (float)
// Note: Uses a small epsilon to avoid division by zero; if squared length <= epsilon, outputs zero vector.

#include <cmath> // for SQRT

static const float kEpsilon = 0.0f; // DAT_00e2cbe0 – likely 0.0 (or very small)
static const float kNormalizationConstant = 1.0f; // DAT_00e2b1a4 – assumed 1.0 for reciprocal

float normalizeVector4(const float* in, float* out)
{
    float x = in[0];
    float y = in[1];
    float z = in[2];
    float w = in[3];

    float sqLen = x * x + y * y + z * z + w * w;

    float length;
    float invScale;

    if (sqLen <= kEpsilon)
    {
        length = 0.0f;
        invScale = 0.0f;
    }
    else
    {
        length = sqrtf(sqLen);
        invScale = kNormalizationConstant / length; // 1 / length
    }

    out[0] = x * invScale;
    out[1] = y * invScale;
    out[2] = z * invScale;
    out[3] = w * invScale;

    return length;
}