// FUNC_NAME: normalizeVector
void normalizeVector(const float* inVec, float* outVec)
{
    // Extract the x component and compute squared length
    float x = inVec[0];
    float lenSq = x * x + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // If length squared is nearly zero (below threshold), output zero vector
    if (lenSq <= gMinLengthSq) {
        lenSq = 0.0f;
    } else {
        // Scale factor to normalize to gTargetLength length
        float invLen = gTargetLength / sqrtf(lenSq);
        outVec[0] = x * invLen;
        outVec[1] = inVec[1] * invLen;
        outVec[2] = inVec[2] * invLen;
        return;
    }

    // Zero vector output
    outVec[0] = 0.0f;
    outVec[1] = 0.0f;
    outVec[2] = 0.0f;
}