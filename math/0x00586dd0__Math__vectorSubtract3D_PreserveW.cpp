// FUNC_NAME: Math::vectorSubtract3D_PreserveW
// Description: Subtracts two 4-element vectors (x,y,z,w) but only modifies the first three components.
// The fourth component of the output vector is preserved.
// Inx86 fastcall: output pointer in EAX (hidden), srcA in EDX, srcB on stack.
void __fastcall vectorSubtract3D_PreserveW(float* out, const float* srcA, const float* srcB)
{
    // Save original w component of the output vector
    float savedW = out[3];

    // Perform componentwise subtraction for x, y, z
    out[0] = srcA[0] - srcB[0]; // x
    out[1] = srcA[1] - srcB[1]; // y
    out[2] = srcA[2] - srcB[2]; // z

    // Restore the w component, ignoring the subtraction result
    out[3] = savedW;
}