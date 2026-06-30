// FUNC_NAME: vectorSubtract3D
// Function at 0x0051e300 subtracts two 4D vectors' x,y,z components, preserving the w component of the output.
// Output pointer is passed in EAX via custom calling convention; reconstructed as first parameter.
void __fastcall vectorSubtract3D(float* outResult, float* vecA, float* vecB)
{
    float tempW = outResult[3]; // Save original w component of result (in_EAX[3])

    outResult[0] = vecA[0] - vecB[0]; // x
    outResult[1] = vecA[1] - vecB[1]; // y
    outResult[2] = vecA[2] - vecB[2]; // z

    outResult[3] = tempW; // Restore original w (unchanged by subtraction)
}