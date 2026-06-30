// FUNC_NAME: Vector4::scale
// Address: 0x0066da80
// Role: Scales a 4-component vector by a scalar and writes to output.
// Fields: x at +0x00, y at +0x04, z at +0x08, w at +0x0C
void __thiscall Vector4::scale(Vector4 *out, float scalar) const
{
    out->x = scalar * this->x;
    out->y = scalar * this->y;
    out->z = scalar * this->z;
    out->w = scalar * this->w;
}