// FUNC_NAME: EARS::Math::vector3AddPreserveW
void __fastcall vector3AddPreserveW(float *out, const float *a, const float *b)
{
    // out in EAX, a in ECX (unused param_1), b in EDX (param_2), but actually param_1 is dummy this
    // Adding only first three components, preserving original w of output
    float origW = out[3];
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = origW;
}