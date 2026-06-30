// FUNC_NAME: MathUtils::normalizeVector3
void __fastcall MathUtils::normalizeVector3(float *outVec, float *inVec)
{
    float lengthSq;
    float invLength;

    // Compute squared length of input vector
    lengthSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // Check against epsilon (DAT_00e2cbe0 is likely a small threshold like 1e-8)
    if (lengthSq <= DAT_00e2cbe0) {
        invLength = 0.0f; // Zero vector, output stays zero
    } else {
        // DAT_00e2b1a4 is likely 1.0f (or a constant like 1.0)
        invLength = DAT_00e2b1a4 / sqrtf(lengthSq);
    }

    // Scale each component by inverse length
    outVec[0] = inVec[0] * invLength;
    outVec[1] = inVec[1] * invLength;
    outVec[2] = inVec[2] * invLength;
}