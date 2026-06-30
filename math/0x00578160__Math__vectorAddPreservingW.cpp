// FUNC_NAME: Math::vectorAddPreservingW
// Function address: 0x00578160
// Purpose: Performs a 3D vector addition (x,y,z) of srcA and srcB into out, preserving the original w component of out.
// This is used for operations like adding a translation vector to a point (where w = 1 is kept constant).

void __fastcall vectorAddPreservingW(float* out, float* srcA, float* srcB)
{
    float w = out[3];              // preserve original fourth component (e.g., homogeneous coordinate)
    out[0] = srcA[0] + srcB[0];    // x
    out[1] = srcA[1] + srcB[1];    // y
    out[2] = srcA[2] + srcB[2];    // z
    out[3] = w;                    // restore w
}