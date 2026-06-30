// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *this, float scalar)
{
    float x = this[0]; // +0x00
    float y = this[1]; // +0x04
    float z = this[2]; // +0x08
    float w = this[3]; // +0x0C

    this[0] = scalar * x;
    this[1] = scalar * y;
    this[2] = scalar * z;
    this[3] = scalar * w;
}