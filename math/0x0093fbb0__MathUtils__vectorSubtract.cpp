// FUNC_NAME: MathUtils::vectorSubtract
void __fastcall MathUtils::vectorSubtract(float *outVec, float *vecA, float *vecB)
{
    // Subtract vecB from vecA, storing result in outVec
    // Preserves the original w component of outVec (likely for homogeneous coordinates)
    float wOut = outVec[3]; // +0x0C: original w component
    
    outVec[0] = vecA[0] - vecB[0]; // x
    outVec[1] = vecA[1] - vecB[1]; // y
    outVec[2] = vecA[2] - vecB[2]; // z
    outVec[3] = wOut;              // w preserved (not overwritten by subtraction)
}