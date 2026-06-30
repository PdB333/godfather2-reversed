// FUNC_NAME: MathUtils::normalizeVector3
void __fastcall normalizeVector3(float* inVector, float* outVector)
{
    float x = inVector[0];
    float y = inVector[1];
    float z = inVector[2];

    float lenSq = x * x + y * y + z * z;

    // If length is nearly zero, output zero vector (avoid division by zero)
    if (lenSq <= 0.0f) // DAT_00e2cbe0 is likely 0.0f
    {
        lenSq = 0.0f;
    }
    else
    {
        lenSq = 1.0f / sqrtf(lenSq); // DAT_00e2b1a4 is 1.0f
    }

    outVector[0] = x * lenSq;
    outVector[1] = y * lenSq;
    outVector[2] = z * lenSq;
}