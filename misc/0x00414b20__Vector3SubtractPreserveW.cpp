// FUNC_NAME: Vector3SubtractPreserveW
void __fastcall Vector3SubtractPreserveW(float* outVec, float* vecA, float* vecB)
{
    float savedW = outVec[3];                     // preserve original fourth component
    outVec[0] = vecA[0] - vecB[0];               // subtract x
    outVec[1] = vecA[1] - vecB[1];               // subtract y
    outVec[2] = vecA[2] - vecB[2];               // subtract z
    outVec[3] = savedW;                          // restore original w
}