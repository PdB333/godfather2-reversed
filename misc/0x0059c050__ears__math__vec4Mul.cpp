// FUNC_NAME: ears::math::vec4Mul
// Function address: 0x0059c050
// Role: Component-wise multiplication of two 4-float vectors (SSE-aligned)
// Source: llmathsse.h (EARS engine math library)
// The function requires all pointers to be 16-byte aligned; asserts otherwise.

void earsMathVec4Mul(const float* __restrict vecA, const float* __restrict vecB,
                 float* __restrict vecDest)
{
    // Debug alignment checks (assert-level in debug builds)
    // Original: LLMATH_CHECK_ALIGNMENT_16(A, "vecA")
    // LLMATH_CHECK_ALIGNMENT_16(B, "vecB")
    // LLMATH_CHECK_ALIGNMENT_16(dest, "dest")
    // This was implemented as a call to a debug print function (0x00670030)
    // if the pointer low 4 bits are non-zero.

    // Perform component-wise multiplication of 4 floats
    float a1 = vecA[1];
    float a2 = vecA[2];
    float a3 = vecA[3];
    float b1 = vecB[1];
    float b2 = vecB[2];
    float b3 = vecB[3];

    vecDest[0] = vecA[0] * vecB[0];
    vecDest[1] = a1 * b1;
    vecDest[2] = a2 * b2;
    vecDest[3] = a3 * b3;
}