// FUNC_NAME: Math::lerp3PreserveW
void __fastcall Math::lerp3PreserveW(float *out, const float *a, const float *b, float t)
{
    // Perform weighted addition of first three components: out = t * a + b
    // Preserve the fourth component (e.g., w for homogeneous coordinates or alpha)
    float oldW = out[3];               // Store the original w component (+0x0C)
    out[0] = t * a[0] + b[0];         // x component
    out[1] = t * a[1] + b[1];         // y component
    out[2] = t * a[2] + b[2];         // z component
    out[3] = oldW;                    // Restore w unchanged
}