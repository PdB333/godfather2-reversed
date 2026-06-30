// FUNC_NAME: vectorSetLength
// Address: 0x005fd6a0
// Scales a 3D vector to a fixed length (defined by DAT_00e2b1a4).
// Input: inputVec (pointer to 3 floats, in ECX)
// Output: outputVec (pointer to 3 floats, in EDX or on stack)
// If vector length is zero (below epsilon DAT_00e2cbe0), output is zero vector.
void __fastcall vectorSetLength(const float* inputVec, float* outputVec)
{
    float x = inputVec[0];
    float y = inputVec[1];
    float z = inputVec[2];
    float squaredLen = x * x + y * y + z * z;
    float scale;
    if (squaredLen <= DAT_00e2cbe0) // small epsilon, avoid division by zero
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(squaredLen); // target length / actual length
    }
    outputVec[0] = x * scale;
    outputVec[1] = y * scale;
    outputVec[2] = z * scale;
}