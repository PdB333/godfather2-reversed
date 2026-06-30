// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(Vector4 *out, float scalar)
{
    // Reads 'this' as input vector (x, y, z, w) at offsets 0x00, 0x04, 0x08, 0x0C
    float x = this->x; // +0x00
    float y = this->y; // +0x04
    float z = this->z; // +0x08
    float w = this->w; // +0x0C

    out->x = scalar * x; // +0x00
    out->y = scalar * y; // +0x04
    out->z = scalar * z; // +0x08
    out->w = scalar * w; // +0x0C
}