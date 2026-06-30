// FUNC_NAME: MathUtils::normalizeVector3
void __fastcall MathUtils::normalizeVector3(float *outVec, float *inVec)
{
    float lengthSq;
    float invLength;

    // Compute squared length of input vector
    lengthSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // Check against epsilon threshold (DAT_00e2cbe0 is likely a small epsilon like 1e-8)
    if (lengthSq <= DAT_00e2cbe0) {
        invLength = 0.0f; // Zero vector, return zero
    }
    else {
        // DAT_00e2b1a4 is likely 1.0f (constant for reciprocal square root)
        invLength = DAT_00e2b1a4 / sqrtf(lengthSq);
    }

    // Normalize each component
    outVec[0] = inVec[0] * invLength;
    outVec[1] = inVec[1] * invLength;
    outVec[2] = inVec[2] * invLength;
}