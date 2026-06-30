// FUNC_NAME: VectorNormalize
// Address: 0x0044d560
// Role: Normalizes a 3D vector in-place with zero-length check (EARS engine)
static const float kNormalizeEpsilon = 0.0f; // DAT_00e2cbe0
static const float kNormalizeFactor  = 1.0f; // DAT_00e2b1a4 (usually 1.0)

void __fastcall VectorNormalize(float *vec)
{
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];

    float lenSq = x * x + y * y + z * z;
    if (lenSq <= kNormalizeEpsilon)
    {
        lenSq = 0.0f;
    }
    else
    {
        lenSq = kNormalizeFactor / sqrtf(lenSq);
    }

    vec[0] = x * lenSq;
    vec[1] = y * lenSq;
    vec[2] = z * lenSq;
}