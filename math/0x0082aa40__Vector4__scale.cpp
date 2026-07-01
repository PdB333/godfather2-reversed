// FUNC_NAME: Vector4::scale
// Address: 0x0082aa40
// Role: Multiply a 4-component vector (this) by a scalar and store result in output vector
void __thiscall Vector4::scale(float *out, float scalar)
{
    float x = this->x; // +0x00
    float y = this->y; // +0x04
    float z = this->z; // +0x08
    float w = this->w; // +0x0C

    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}