// FUNC_NAME: Vector4::scaleTo
void __thiscall Vector4::scaleTo(float *out, float scalar) const
{
    // this points to a Vector4 (4 floats: x, y, z, w at offsets +0x00, +0x04, +0x08, +0x0C)
    float x = this->x; // +0x00
    float y = this->y; // +0x04
    float z = this->z; // +0x08
    float w = this->w; // +0x0C

    out[0] = x * scalar;
    out[1] = y * scalar;
    out[2] = z * scalar;
    out[3] = w * scalar;
}