// FUNC_NAME: Math::normalizeVector3
void __fastcall Math::normalizeVector3(float *outVec, float *inVec)
{
    float const *src = inVec;
    float *dst = outVec;

    float lenSq = src[0] * src[0] + src[1] * src[1] + src[2] * src[2];

    float invLen;
    if (lenSq <= 0.0f) {
        invLen = 0.0f;
    } else {
        invLen = 1.0f / __fsqrt(lenSq);
    }

    dst[0] = src[0] * invLen;
    dst[1] = src[1] * invLen;
    dst[2] = src[2] * invLen;
}