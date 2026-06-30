// FUNC_NAME: lerpVector3PreserveW
void __fastcall lerpVector3PreserveW(float *out, const float *a, const float *b, float t)
{
    float wOriginal = out[3];

    out[0] = t * a[0] + b[0];
    out[1] = t * a[1] + b[1];
    out[2] = t * a[2] + b[2];
    // Lerp the fourth component but then restore original (preserve w)
    out[3] = t * a[3] + b[3];
    out[3] = wOriginal;
}