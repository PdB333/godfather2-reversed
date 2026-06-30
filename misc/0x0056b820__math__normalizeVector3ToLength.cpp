// FUNC_NAME: math::normalizeVector3ToLength
// Address: 0x0056b820
// Purpose: Normalize a 3D vector to a specific length (stored in global constant g_targetLength).
// If the squared length is below an epsilon, the result is zeroed out.
// Original fastcall: in_EAX points to input vector, param_1 (on stack) points to output vector.
// Reconstructed as: void normalizeVector3ToLength(float *outVec, const float *inVec);

// Constants from data references
static const float kEpsilon = 0.0001f;     // DAT_00e2cbe0
static const float kTargetLength = 1.0f;   // DAT_00e2b1a4 (assumed, actual value unknown)

void normalizeVector3ToLength(float *outVec, const float *inVec)
{
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];

    float lenSq = x*x + y*y + z*z;

    float scale;
    if (lenSq <= kEpsilon)
    {
        scale = 0.0f;
    }
    else
    {
        scale = kTargetLength / sqrtf(lenSq);
    }

    outVec[0] = x * scale;
    outVec[1] = y * scale;
    outVec[2] = z * scale;
}