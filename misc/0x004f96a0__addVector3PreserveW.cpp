// FUNC_NAME: addVector3PreserveW
// Address: 0x004f96a0
// Role: Adds two 4-component vectors but only the x,y,z components are summed.
// The w component of the output vector is preserved (unchanged).
// This is likely used for adding a translation to a position while keeping the homogeneous w coordinate.

void __fastcall addVector3PreserveW(float* outVec, float* inVec1, float* inVec2)
{
    float origW = outVec[3];
    outVec[0] = inVec1[0] + inVec2[0]; // x
    outVec[1] = inVec1[1] + inVec2[1]; // y
    outVec[2] = inVec1[2] + inVec2[2]; // z
    outVec[3] = origW; // w preserved
}