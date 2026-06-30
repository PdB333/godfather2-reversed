// FUNC_NAME: Math::safeNormalize

void safeNormalize(float* outVec, const float* inVec)
{
    // Constants from global data (offsets TBD)
    const float kLengthThresholdSq = *(float*)0x00e2cbe0; // Squared threshold for zero vector check
    const float kNormalizeTarget = *(float*)0x00e2b1a4;   // Desired length after normalization (e.g., 1.0f)

    float x = inVec[0];
    float lenSq = x * x + inVec[1] * inVec[1] + inVec[2] * inVec[2];
    float scale;

    if (lenSq <= kLengthThresholdSq)
    {
        scale = 0.0f;
    }
    else
    {
        scale = kNormalizeTarget / sqrtf(lenSq);
    }

    outVec[0] = x * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}