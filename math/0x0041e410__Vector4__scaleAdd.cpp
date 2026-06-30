// FUNC_NAME: Vector4::scaleAdd
void __thiscall Vector4::scaleAdd(float *a, float *b, float *out)
{
    // Component-wise fused multiply-add: out[i] = this[i] * a[i] + b[i]
    out[0] = this[0] * a[0] + b[0];
    out[1] = this[1] * a[1] + b[1];
    out[2] = this[2] * a[2] + b[2];
    out[3] = this[3] * a[3] + b[3];
}