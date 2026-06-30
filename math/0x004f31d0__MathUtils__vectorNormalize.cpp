// FUNC_NAME: MathUtils::vectorNormalize
void __fastcall vectorNormalize(float *out, float *in)
{
    // Compute squared length
    float lengthSq = in[0] * in[0] + in[1] * in[1] + in[2] * in[2];

    // Constant epsilon to avoid division by zero
    const float kEpsilon = *(float*)0x00e2cbe0; // typically a small value like 1e-6f
    // Factor to scale normalized vector (usually 1.0f, allows custom scaling)
    const float kScale = *(float*)0x00e2b1a4;   // typically 1.0f

    float scale;
    if (lengthSq <= kEpsilon)
    {
        scale = 0.0f;
    }
    else
    {
        scale = kScale / sqrtf(lengthSq);
    }

    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
}