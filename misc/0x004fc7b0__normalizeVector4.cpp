// FUNC_NAME: normalizeVector4
void __fastcall normalizeVector4(float *outVec, float *inVec) {
    float scale;
    float lenSq = inVec[0]*inVec[0] + inVec[1]*inVec[1] + inVec[2]*inVec[2] + inVec[3]*inVec[3];
    // If vector is too short, zero it out to avoid division by zero
    if (lenSq <= 0.00001f) {  // DAT_00e2cbe0 = epsilon
        scale = 0.0f;
    } else {
        scale = 1.0f / (float)sqrt(lenSq);  // DAT_00e2b1a4 = 1.0
    }
    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
    outVec[3] = inVec[3] * scale;
    // Returns nothing, modifies outVec
}