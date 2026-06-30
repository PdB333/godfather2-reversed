// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const Vector4& other, Vector4& out) const
{
    // Subtract the 'other' vector from this vector component-wise
    // out = this - other
    out.x = this->x - other.x;
    out.y = this->y - other.y;
    out.z = this->z - other.z;
    out.w = this->w - other.w;
}