// FUNC_NAME: math_vector3_subtract_preserve_w
void __fastcall math_vector3_subtract_preserve_w(float* out, const float* a, const float* b)
{
    // Subtract only the x, y, z components of two 4‑float vectors,
    // leaving the w component of the output unchanged.
    // Equivalent to: out->x = a->x - b->x; out->y = a->y - b->y; out->z = a->z - b->z; out->w untouched.
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];
    float originalW = out[3]; // preserve existing w component of output

    out[0] = a[0] - b[0];
    out[1] = a1 - b1;
    out[2] = a2 - b2;
    out[3] = a3 - b3; // temporary, then overwritten
    out[3] = originalW;
}