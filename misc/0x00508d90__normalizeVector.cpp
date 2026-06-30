// FUNC_NAME: normalizeVector
#include <cmath>  // for sqrtf

/**
 * Normalize a 3D vector.
 * If the squared length is <= a small epsilon, the output is set to zero to avoid division by zero.
 * 
 * @param output  pointer to 3 floats to receive the normalized vector
 * @param input   pointer to 3 floats representing the input vector (read via EAX register in original assembly)
 */
void __fastcall normalizeVector(float *output, float *input)
{
    // Constants from the original binary (DAT_00e2cbe0 = epsilon, DAT_00e2b1a4 = 1.0f)
    const float kEpsilon = 1e-6f;   // small threshold for zero-length
    const float kScale   = 1.0f;    // reciprocal multiplier

    float lenSq = input[0] * input[0] + input[1] * input[1] + input[2] * input[2];

    if (lenSq <= kEpsilon) {
        output[0] = 0.0f;
        output[1] = 0.0f;
        output[2] = 0.0f;
        return;
    }

    float invLen = kScale / sqrtf(lenSq);   // equivalent to 1.0 / sqrt(lenSq)
    output[0] = input[0] * invLen;
    output[1] = input[1] * invLen;
    output[2] = input[2] * invLen;
}