// FUNC_NAME: normalizeVector
void __fastcall normalizeVector(float *outVec)
{
    float *inVec = (float *)in_EAX; // Source vector passed in EAX (likely a register convention)
    float sqLen = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];
    float scale;
    if (sqLen <= DAT_00e2cbe0) // Minimum length threshold (e.g., 1e-6)
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(sqLen); // Target length (e.g., 1.0f)
    }
    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}