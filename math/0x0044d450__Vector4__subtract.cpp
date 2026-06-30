// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const Vector4& other, Vector4& out) const
{
    // Subtract two 4-component vectors: out = this - other
    out.x = this->x - other.x; // +0x00
    out.y = this->y - other.y; // +0x04
    out.z = this->z - other.z; // +0x08
    out.w = this->w - other.w; // +0x0C
}