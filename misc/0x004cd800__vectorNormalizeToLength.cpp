// FUNC_NAME: vectorNormalizeToLength
void __fastcall vectorNormalizeToLength(float* outVec)
{
    float lengthSq;
    float scale;

    // Compute squared length of input vector (inVec is same as outVec for in-place)
    lengthSq = outVec[0] * outVec[0] + outVec[1] * outVec[1] + outVec[2] * outVec[2];

    // If vector is too small, set to zero to avoid division by zero
    if (lengthSq <= kEpsilonSquared) // DAT_00e2cbe0
    {
        scale = 0.0f;
    }
    else
    {
        // Scale to target length (DAT_00e2b1a4) divided by actual length
        scale = kTargetLength / sqrtf(lengthSq); // DAT_00e2b1a4
    }

    outVec[0] *= scale;
    outVec[1] *= scale;
    outVec[2] *= scale;
}