// FUNC_NAME: Math::normalizeVector
// Function: Normalize a 3D vector (scale to unit length) with epsilon check.
// Takes input vector pointer in ECX (fastcall), output vector pointer in EDX.
// Uses global constants for epsilon and normalization factor (assumed 1.0).
// Address: 0x004f9850
#include <cmath>

// Global constants from data section (values assumed for common usage)
const float kEpsilonSqr = 0.0f;       // DAT_00e2cbe0 - threshold for zero-length
const float kNormalizeFactor = 1.0f;  // DAT_00e2b1a4 - scale factor (usually 1.0)

void __fastcall normalizeVector(const float* pInput, float* pOutput)
{
    float x = pInput[0];
    float y = pInput[1];
    float z = pInput[2];

    float lenSqr = x * x + y * y + z * z;

    float scale;
    if (lenSqr <= kEpsilonSqr) {
        scale = 0.0f;                 // zero vector -> result is zero
    } else {
        scale = kNormalizeFactor / std::sqrt(lenSqr);
    }

    pOutput[0] = x * scale;
    pOutput[1] = y * scale;
    pOutput[2] = z * scale;
}