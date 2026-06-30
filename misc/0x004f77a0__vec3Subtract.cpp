// FUNC_NAME: vec3Subtract
void __fastcall vec3Subtract(float *out, float *a, float *b)
{
    // out[0..2] = a[0..2] - b[0..2]; out[3] unchanged
    float origW = out[3];
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
    out[3] = origW;
}