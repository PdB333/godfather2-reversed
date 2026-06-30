// FUNC_NAME: Vector4::add
// Address: 0x0049e760 - Adds two 4-component vectors (this + other) and stores result in out.
void __thiscall Vector4::add(const Vector4& other, Vector4& out) const
{
    // Components: x, y, z, w (offsets +0x00, +0x04, +0x08, +0x0C)
    out.x = this->x + other.x;
    out.y = this->y + other.y;
    out.z = this->z + other.z;
    out.w = this->w + other.w;
}