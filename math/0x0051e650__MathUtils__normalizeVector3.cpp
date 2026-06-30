// FUNC_NAME: MathUtils::normalizeVector3
void __fastcall MathUtils::normalizeVector3(float *outVec, float *inVec)
{
    float lengthSq;
    float invLength;

    // Compute squared length of input vector
    lengthSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // Check if length is effectively zero (using a small epsilon from global data)
    if (lengthSq <= DAT_00e2cbe0) { // +0x00: epsilon threshold for zero-length vector
        invLength = 0.0f;
    }
    else {
        // Compute inverse square root for normalization
        invLength = DAT_00e2b1a4 / SQRT(lengthSq); // +0x00: 1.0f constant
    }

    // Write normalized components to output
    outVec[0] = inVec[0] * invLength;
    outVec[1] = inVec[1] * invLength;
    outVec[2] = inVec[2] * invLength;
}