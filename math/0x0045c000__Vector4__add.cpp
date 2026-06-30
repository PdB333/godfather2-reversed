// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(const Vector4& rhs, Vector4& out) const
{
    out.x = this->x + rhs.x;
    out.y = this->y + rhs.y;
    out.z = this->z + rhs.z;
    out.w = this->w + rhs.w;
}