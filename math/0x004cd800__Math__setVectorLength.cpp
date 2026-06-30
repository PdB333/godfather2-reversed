// FUNC_NAME: Math::setVectorLength
void __cdecl Math::setVectorLength(const float* inVec, float* outVec)
{
    // +0x00: x, +0x04: y, +0x08: z
    float vx = inVec[0];
    float vy = inVec[1];
    float vz = inVec[2];

    float lenSq = vx * vx + vy * vy + vz * vz;

    // Global constants: epsilonSq (0x00e2cbe0) and targetLength (0x00e2b1a4)
    if (lenSq <= DAT_00e2cbe0)  // zero vector threshold
    {
        lenSq = 0.0f;            // will force output to zero
    }
    else
    {
        lenSq = DAT_00e2b1a4 / sqrtf(lenSq);  // scale factor to achieve target length
    }

    outVec[0] = vx * lenSq;
    outVec[1] = vy * lenSq;
    outVec[2] = vz * lenSq;
}