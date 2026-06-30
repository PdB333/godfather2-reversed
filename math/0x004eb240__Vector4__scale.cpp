// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *out, float scalar) const
{
    // Scale the 4-component vector (x, y, z, w) by a scalar and store in output
    float x = this->x; // +0x00
    float y = this->y; // +0x04
    float z = this->z; // +0x08
    float w = this->w; // +0x0C

    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}