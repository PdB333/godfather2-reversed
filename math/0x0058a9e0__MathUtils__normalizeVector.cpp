// FUNC_NAME: MathUtils::normalizeVector

#include <cmath>

// Global constants (addresses 0x00e2cbe0 and 0x00e2b1a4)
// Typically epsilon for zero-length vector check and normalization factor (e.g., 1.0f)
static const float kNormalizeEpsilon = *(float*)0x00e2cbe0;
static const float kNormalizeFactor = *(float*)0x00e2b1a4;

// __fastcall: first parameter (ECX) is output, second (EDX) is input
void __fastcall normalizeVector(float* out, const float* in)
{
    // Compute squared length of input vector (x, y, z)
    float lenSq = in[0] * in[0] + in[1] * in[1] + in[2] * in[2];

    float scale;
    if (lenSq <= kNormalizeEpsilon)
    {
        scale = 0.0f;
    }
    else
    {
        // Apply normalization factor (usually 1.0) divided by actual length
        scale = kNormalizeFactor / std::sqrt(lenSq);
    }

    // Scale each component
    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
}