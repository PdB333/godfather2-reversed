// FUNC_NAME: normalizeVector
// Address: 0x0043a210
// Description: Normalizes a 3D vector (inVec) and writes the unit vector into outVec.
// Returns the length of the original vector. If the squared length is <= g_normalizeEpsilon,
// the output is set to zero and the returned length is 0.0.
// The scaling factor for normalization (g_invLengthFactor) is typically 1.0f.
// Used extensively across the EARS engine for vector normalization.

// Global epsilon for zero-length vector detection (squared threshold)
extern float g_normalizeEpsilon; // = DAT_00e2cbe0
// Factor used to compute inverse length (typically 1.0f)
extern float g_invLengthFactor; // = DAT_00e2b1a4

float normalizeVector(float outVec[3], const float inVec[3])
{
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];
    float sqLen = x * x + y * y + z * z;

    if (sqLen <= g_normalizeEpsilon) {
        // Zero or near-zero vector: output zero vector
        outVec[0] = 0.0f;
        outVec[1] = 0.0f;
        outVec[2] = 0.0f;
        return 0.0f;
    } else {
        float len = sqrtf(sqLen);          // actual length
        float invLen = g_invLengthFactor / len; // 1.0f / len
        outVec[0] = x * invLen;
        outVec[1] = y * invLen;
        outVec[2] = z * invLen;
        return len; // return original length
    }
}