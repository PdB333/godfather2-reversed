// FUNC_NAME: Vector4SubtractPreserveW
void __fastcall Vector4SubtractPreserveW(float* dst, const float* a, const float* b)
{
    // dst[0..2] = a[0..2] - b[0..2], dst[3] (w) remains unchanged
    float savedW = dst[3];
    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
    dst[2] = a[2] - b[2];
    dst[3] = savedW;
}