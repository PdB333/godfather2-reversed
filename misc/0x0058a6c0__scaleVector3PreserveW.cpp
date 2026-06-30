// FUNC_NAME: scaleVector3PreserveW
// Address: 0x0058a6c0
// Scales the first three components of a 4-element vector by a scalar, preserving the fourth component (e.g., w for homogeneous coordinates).
void __fastcall scaleVector3PreserveW(float* outVec, const float* inVec, float scale)
{
    float origW = outVec[3];  // save original fourth component

    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
    outVec[3] = origW;        // restore unchanged w
}