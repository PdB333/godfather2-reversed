// FUNC_NAME: vectorNormalize
// Address: 0x0054ba20
// Role: Normalizes a 3D vector (param_2) and stores result in param_1.
// Returns 1 if original vector length > 0, else 0. Optionally stores original length via param_3.

// Based on EA EARS math library conventions.
// Constants:
//   0x00e2cbe0 = squared epsilon (likely 1e-8 or similar)
//   0x00e2b1a4 = 1.0f (used as reciprocal factor)

int vectorNormalize(float* outVec, float* inVec, float* outLength) {
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];

    float sqLen = x*x + y*y + z*z;

    // Epsilon check (square) - avoid division by zero
    if (sqLen <= SQUARED_EPSILON) {
        outVec[0] = 0.0f;
        outVec[1] = 0.0f;
        outVec[2] = 0.0f;
        sqLen = 0.0f;  // used as length later
    } else {
        float len = sqrtf(sqLen);
        float invLen = 1.0f / len;  // 0x00e2b1a4 is 1.0f
        outVec[0] = x * invLen;
        outVec[1] = y * invLen;
        outVec[2] = z * invLen;
        sqLen = len;  // reuse variable to hold length
    }

    if (outLength != nullptr) {
        *outLength = sqLen;  // either 0 or actual length
    }

    return (sqLen > 0.0f) ? 1 : 0;
}