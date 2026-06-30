// FUNC_NAME: scaleVector3
void __cdecl scaleVector3(float* dest, const float* srcA, const float* srcB)
{
    // Performs component-wise multiplication of two 4-element float arrays,
    // but preserves the fourth element of dest (e.g., for 3D vectors with a homogeneous w component).
    dest[0] = srcA[0] * srcB[0];
    dest[1] = srcA[1] * srcB[1];
    dest[2] = srcA[2] * srcB[2];
    // dest[3] remains unchanged
}