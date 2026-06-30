// FUNC_NAME: math_vector3_subtract_preserve_w
// Function address: 0x006da490
// Subtracts two 3D vectors (x,y,z) and writes the result to a destination,
// preserving the destination's original w component.
// Signature: void __fastcall vectorSubtract3(float* dst, const float* srcA, const float* srcB)
// Parameters: dst in EAX, srcA in EDX, srcB on stack (param_1 in ECX unused)

void __fastcall vectorSubtract3(float* dst, const float* srcA, const float* srcB)
{
    float tempX = srcA[0] - srcB[0];
    float tempY = srcA[1] - srcB[1];
    float tempZ = srcA[2] - srcB[2];
    // Preserve the original w component of the destination
    float savedW = dst[3];

    dst[0] = tempX;
    dst[1] = tempY;
    dst[2] = tempZ;
    dst[3] = savedW;
}