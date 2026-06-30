// FUNC_NAME: Vector4::lerp
void __thiscall Vector4::lerp(const Vector4& end, float t, Vector4& out) const
{
    // Linear interpolation between this (start) and end, storing result in out
    out.x = (end.x - this->x) * t + this->x;
    out.y = (end.y - this->y) * t + this->y;
    out.z = (end.z - this->z) * t + this->z;
    out.w = (end.w - this->w) * t + this->w;
}