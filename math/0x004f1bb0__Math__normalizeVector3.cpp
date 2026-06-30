// FUNC_NAME: Math::normalizeVector3
void __fastcall Math::normalizeVector3(float *outVec, float *inVec)
{
    float lengthSq;
    float invLength;

    // Compute squared length of input vector
    lengthSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // Check if length is near zero (using epsilon threshold from DAT_00e2cbe0)
    if (lengthSq <= DAT_00e2cbe0) {
        invLength = 0.0f;
    }
    else {
        // Compute reciprocal of length (DAT_00e2b1a4 is likely 1.0f)
        invLength = DAT_00e2b1a4 / SQRT(lengthSq);
    }

    // Normalize each component
    outVec[0] = inVec[0] * invLength;
    outVec[1] = inVec[1] * invLength;
    outVec[2] = inVec[2] * invLength;
}