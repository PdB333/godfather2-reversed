// FUNC_NAME: MathUtils::vector3Normalize
void __fastcall vector3Normalize(float *outVector, float *inVector)
{
    float fSqrLength;
    float fInvLength;
    const float epsilon = 0.0f; // DAT_00e2cbe0 (threshold for zero-length)
    const float scale = 1.0f;   // DAT_00e2b1a4 (normalization factor, typically 1.0)

    fSqrLength = inVector[0] * inVector[0] + inVector[1] * inVector[1] + inVector[2] * inVector[2];
    if (fSqrLength <= epsilon)
    {
        fInvLength = 0.0f;
    }
    else
    {
        fInvLength = scale / sqrt(fSqrLength);
    }
    outVector[0] = inVector[0] * fInvLength;
    outVector[1] = inVector[1] * fInvLength;
    outVector[2] = inVector[2] * fInvLength;
}