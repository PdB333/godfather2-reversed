// FUNC_NAME: Math::vectorNormalize
// Function at 0x004f8820: Normalize a 3D vector to a specific length (DAT_00e2b1a4) with a threshold to avoid division by zero.
// Input vector pointer in EAX (passed via register), output vector pointer as parameter (EDX in fastcall convention).
// Uses two globals: DAT_00e2cbe0 (squared epsilon threshold) and DAT_00e2b1a4 (target magnitude).
void __fastcall Math::vectorNormalize(const float* inVec, float* outVec) {
    float lenSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];
    float scale;

    // If the squared length is below epsilon, output zero vector
    if (lenSq <= DAT_00e2cbe0) { // Squared epsilon threshold
        scale = 0.0f;
    } else {
        // Scale factor to achieve target length (e.g., 1.0 for unit vector, or physics scale)
        scale = DAT_00e2b1a4 / sqrtf(lenSq); // Target magnitude / actual length
    }

    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}