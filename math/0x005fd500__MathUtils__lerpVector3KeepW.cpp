// FUNC_NAME: MathUtils::lerpVector3KeepW
void __fastcall lerpVector3KeepW(float* out, float* a, float* b, float t)
{
    // Linear interpolation of first three components: out.xyz = t * a.xyz + b.xyz
    // The w component (out[3]) is preserved unchanged.
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // unused in computation
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // unused
    float originalW = out[3]; // preserve original w

    out[0] = t * ax + bx;
    out[1] = t * ay + by;
    out[2] = t * az + bz;
    out[3] = originalW; // restore w
}