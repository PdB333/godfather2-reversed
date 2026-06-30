// FUNC_NAME: Math::scaleVectorToMagnitude
// Function address: 0x00613080
// Identified role: Normalizes a 3D vector to a fixed magnitude (DAT_00e2b1a4), with zero-length threshold (DAT_00e2cbe0).
// Input: in_EAX (source vector pointer), param_1 (destination vector pointer)
// Global constants:
//   DAT_00e2cbe0 - epsilon threshold for zero-length (likely 0.0f or very small)
//   DAT_00e2b1a4 - target magnitude after scaling

void __fastcall Math::scaleVectorToMagnitude(float *srcVec, float *destVec) {
    float lengthSq;
    float scaleFactor;

    // Compute squared length of source vector
    lengthSq = srcVec[0] * srcVec[0] + srcVec[1] * srcVec[1] + srcVec[2] * srcVec[2];

    // If below epsilon, output zero vector
    if (lengthSq <= DAT_00e2cbe0) {
        scaleFactor = 0.0f;
    } else {
        // Scale factor = target magnitude / actual length
        scaleFactor = DAT_00e2b1a4 / sqrtf(lengthSq);
    }

    // Scale source vector and store to destination
    destVec[0] = srcVec[0] * scaleFactor;
    destVec[1] = srcVec[1] * scaleFactor;
    destVec[2] = srcVec[2] * scaleFactor;
}