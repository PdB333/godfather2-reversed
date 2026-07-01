// FUNC_NAME: math::scaleVector3PreserveW
void __fastcall scaleVector3PreserveW(float* outVec, float* inVec, float scale)
{
    float y = inVec[1]; // inVec.y
    float z = inVec[2]; // inVec.z
    float w = inVec[3]; // inVec.w (homogeneous component, kept unchanged)
    float originalOutW = outVec[3]; // preserve destination w

    outVec[0] = scale * inVec[0]; // x
    outVec[1] = scale * y;        // y
    outVec[2] = scale * z;        // z
    outVec[3] = originalOutW;     // unchanged

    return;
}