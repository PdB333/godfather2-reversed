// FUNC_NAME: normalizeVector
void __fastcall normalizeVector(float *outVec, const float *inVec)
{
    float lenSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];
    float scale;
    if (lenSq <= /* epsilon */ 0.0f) { // DAT_00e2cbe0 is likely 0.0 or very small
        scale = 0.0f;
    } else {
        scale = /* target magnitude */ 1.0f / sqrtf(lenSq); // DAT_00e2b1a4 is 1.0f
    }
    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}