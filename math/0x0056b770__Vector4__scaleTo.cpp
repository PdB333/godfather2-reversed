// FUNC_NAME: Vector4::scaleTo
// Address: 0x0056b770
// Role: Scales a 4-component vector (this) by a scalar and writes result to output vector.
// Members: this[0..3] = x, y, z, w components. Output stored in out[0..3].
void __thiscall Vector4::scaleTo(float *out, float scalar)
{
    float x = this[0];
    float y = this[1];
    float z = this[2];
    float w = this[3];

    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}