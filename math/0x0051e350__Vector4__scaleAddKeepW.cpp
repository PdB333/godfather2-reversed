// FUNC_NAME: Vector4::scaleAddKeepW
void __fastcall Vector4::scaleAddKeepW(float* out, const float* a, const float* b, float t)
{
    float oldW = out[3];
    out[0] = t * a[0] + b[0];
    out[1] = t * a[1] + b[1];
    out[2] = t * a[2] + b[2];
    out[3] = t * a[3] + b[3];
    out[3] = oldW; // preserve the fourth component (e.g., homogeneous w or quaternion scalar)
}