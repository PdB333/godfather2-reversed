// FUNC_NAME: Math::normalizeVector3
void __fastcall Math::normalizeVector3(float *outputVec, float *inputVec)
{
    float fVar1;
    float lengthSq;
    
    fVar1 = inputVec[0];
    // +0x00 x, +0x04 y, +0x08 z
    lengthSq = inputVec[0] * inputVec[0] + inputVec[1] * inputVec[1] + inputVec[2] * inputVec[2];
    if (lengthSq <= 0.0f) // DAT_00e2cbe0 is likely 0.0 or a very small epsilon
    {
        lengthSq = 0.0f;
    }
    else
    {
        lengthSq = 1.0f / sqrtf(lengthSq); // DAT_00e2b1a4 is likely 1.0f
    }
    outputVec[0] = fVar1 * lengthSq;
    outputVec[1] = lengthSq * inputVec[1];
    outputVec[2] = lengthSq * inputVec[2];
}