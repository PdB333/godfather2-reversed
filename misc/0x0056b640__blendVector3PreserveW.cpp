// FUNC_NAME: blendVector3PreserveW
void __fastcall blendVector3PreserveW(int /*ecx*/, float *vecA, float weightB, float *vecB, float weightA)
{
    // Performs a weighted sum of two 4D vectors (only first 3 components blended),
    // leaving the 4th component (index 3) unchanged.
    // This is used for position blending while preserving homogeneous coordinate.
    float aX = vecA[0];
    float aY = vecA[1];
    float aZ = vecA[2];
    float aW = vecA[3];  // read but not used in blend; kept for completeness
    float bX = vecB[0];
    float bY = vecB[1];
    float bZ = vecB[2];
    float bW = vecB[3];
    // in_EAX points to output vector (passed in EAX register, not as explicit parameter)
    float *out = (float *)_EAX; // pseudo-register; in real code this is implicit
    float origOutW = out[3];   // preserve original output w
    out[0] = weightA * aX + weightB * bX;
    out[1] = weightA * aY + weightB * bY;
    out[2] = weightA * aZ + weightB * bZ;
    out[3] = origOutW;
}