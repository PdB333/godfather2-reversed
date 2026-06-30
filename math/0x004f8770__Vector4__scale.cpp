// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *this, float *out, float scalar)
{
    float x = this[0]; // +0x00
    float y = this[1]; // +0x04
    float z = this[2]; // +0x08
    float w = this[3]; // +0x0C

    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}