// FUNC_NAME: scaleVector3KeepW
void __fastcall scaleVector3KeepW(float *outVec, float *inVec, float scale)
{
    // Scale the first three components of inVec by scale and write to outVec,
    // while preserving the fourth component (w) of outVec.
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];
    float wOriginal = outVec[3]; // preserve outVec's w

    outVec[0] = scale * x;
    outVec[1] = scale * y;
    outVec[2] = scale * z;
    outVec[3] = wOriginal; // restore w
}