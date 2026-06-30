// FUNC_NAME: EARSMath::scaleToMagnitude
void __fastcall EARSMath::scaleToMagnitude(const float* inVector, float* outVector)
{
    float srcX = inVector[0];
    float lenSq = srcX * srcX + inVector[1] * inVector[1] + inVector[2] * inVector[2];

    // Threshold to avoid division by zero (likely a small epsilon, e.g., 1e-6²)
    if (lenSq <= DAT_00e2cbe0)
    {
        lenSq = 0.0f;
    }
    else
    {
        // Target magnitude (probably 1.0f for normalization, or a fixed radius)
        lenSq = DAT_00e2b1a4 * EARSMath::invSqrt(lenSq);  // or SQRT then divide, see below
        // NOTE: The original uses SQRT and then divide: DAT_00e2b1a4 / sqrt(lenSq)
    }
    // Scale each component by lenSq (which is now scaleFactor)
    outVector[0] = srcX * lenSq;
    outVector[1] = inVector[1] * lenSq;
    outVector[2] = inVector[2] * lenSq;
}