// FUNC_NAME: scaleVector3DPreservingW
void __fastcall scaleVector3DPreservingW(float* outVec, float* inVec, float scale)
{
    // Preserve the w component (index 3) of the output vector
    float w = outVec[3];

    // Scale the x,y,z components of the input vector and store in output
    outVec[0] = scale * inVec[0];
    outVec[1] = scale * inVec[1];
    outVec[2] = scale * inVec[2];

    // Restore the original w component (homogeneous coordinate or padding)
    outVec[3] = w;
}