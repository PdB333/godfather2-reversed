// FUNC_NAME: LinearInterpolateVec3KeepW
void __fastcall LinearInterpolateVec3KeepW(float* out, const float* a, const float* b, float t)
{
    // Interpolate x, y, z components between vectors a and b by factor t
    // The w component (out[3]) is preserved and not modified
    out[0] = a[0] + (b[0] - a[0]) * t; // x
    out[1] = a[1] + (b[1] - a[1]) * t; // y
    out[2] = a[2] + (b[2] - a[2]) * t; // z
    // w is left untouched
}