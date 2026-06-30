// FUNC_NAME: lerpVector3PreserveW
void __fastcall lerpVector3PreserveW(float* outVec, float* vecA, float* vecB, float t)
{
    // Read vecA components
    float ax = vecA[0];
    float ay = vecA[1];
    float az = vecA[2];
    // vecA[3] is read but unused (dead store)

    // Read vecB components
    float bx = vecB[0];
    float by = vecB[1];
    float bz = vecB[2];

    // Preserve the original w component of the output before overwriting
    float origOutW = outVec[3];

    // Perform 3D linear interpolation: outVec = t * vecA + vecB
    outVec[0] = t * ax + bx;
    outVec[1] = t * ay + by;
    outVec[2] = t * az + bz;

    // Restore the w component (since it was preserved, not computed)
    outVec[3] = origOutW;
}