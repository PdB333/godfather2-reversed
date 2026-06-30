// FUNC_NAME: vec3ScaleAddPreserveW
void __fastcall vec3ScaleAddPreserveW(float *out, float *a, float *b, float t)
{
    // 0x0058a780: 3D vector linear blend: out.xyz = a.xyz * t + b.xyz, out.w unchanged
    float oldW = out[3]; // preserve the fourth component (e.g., homogeneous w)
    out[0] = a[0] * t + b[0];
    out[1] = a[1] * t + b[1];
    out[2] = a[2] * t + b[2];
    out[3] = oldW;
}