// FUN_004734f0: Math::vector3Subtract4D
void __fastcall Math::vector3Subtract4D(float* result, float* vecA, float* vecB)
{
    // In original binary, result pointer is passed in EAX, vecA in EDX, vecB on stack.
    // Subtracts the x,y,z components of two 4D vectors (vecA - vecB) and stores into result.
    // The w component (index 3) of result is preserved.
    float savedW = result[3];
    result[0] = vecA[0] - vecB[0];
    result[1] = vecA[1] - vecB[1];
    result[2] = vecA[2] - vecB[2];
    result[3] = savedW;
}