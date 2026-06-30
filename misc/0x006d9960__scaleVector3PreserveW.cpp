// FUNC_NAME: scaleVector3PreserveW
// Address: 0x006d9960
// Role: Scales the (x,y,z) components of a 3D vector (in homogeneous form with w)
//        by a scalar, preserving the original w component of the output vector.
//        Used in EA EARS engine math library for vector operations.

void __fastcall scaleVector3PreserveW(float* outVec, float* inVec, float scalar)
{
    // Capture original w component of output vector before modification
    float outW = outVec[3];

    // Scale the first three components from input vector
    outVec[0] = scalar * inVec[0]; // x
    outVec[1] = scalar * inVec[1]; // y
    outVec[2] = scalar * inVec[2]; // z

    // Temporarily set w to scaled version, then restore original output w
    outVec[3] = scalar * inVec[3]; // overwritten next line
    outVec[3] = outW;              // preserve original w
}