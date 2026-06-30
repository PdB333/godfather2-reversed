// FUNC_NAME: Math::normalizeQuaternionMakeWPositive
// Address: 0x0055aa00
// Role: Normalizes a quaternion (using only xyz for length) and ensures w is positive by negating if original w <= 0.
// Note: The normalization only uses the vector part (x,y,z) – this may be intentional for a specific representation.
// DAT_00e44564 is assumed to be 0.0f (negation) based on typical quaternion sign correction.

void __thiscall Math::normalizeQuaternionMakeWPositive(const float* inQuat, float* outQuat)
{
    // Copy input quaternion to output
    outQuat[0] = inQuat[0]; // x
    outQuat[1] = inQuat[1]; // y
    outQuat[2] = inQuat[2]; // z
    outQuat[3] = inQuat[3]; // w

    // Compute squared length of vector part (x,y,z)
    float lenSq = outQuat[0] * outQuat[0] + outQuat[1] * outQuat[1] + outQuat[2] * outQuat[2];

    if (lenSq != 0.0f)
    {
        // Compute reciprocal square root using x87 long double precision
        float invLen = 1.0f / sqrtf(lenSq); // FUN_00414a80 is sqrtf, then 1/sqrt
        // Normalize all four components by the same factor (only xyz length)
        outQuat[0] *= invLen;
        outQuat[1] *= invLen;
        outQuat[2] *= invLen;
        outQuat[3] *= invLen;
    }

    // If original w is negative (and non-zero), negate the entire quaternion to make w positive
    // DAT_00e44564 is a global constant; assumed to be 0.0f for negation
    const float kNegateConst = 0.0f; // DAT_00e44564
    if (inQuat[3] <= 0.0f && inQuat[3] != 0.0f)
    {
        outQuat[0] = kNegateConst - outQuat[0];
        outQuat[1] = kNegateConst - outQuat[1];
        outQuat[2] = kNegateConst - outQuat[2];
        outQuat[3] = kNegateConst - outQuat[3];
    }
}