// FUNC_NAME: Vector4::lerpTo (0x00514470)
void __thiscall Vector4::lerpTo(const Vector4& end, float t, Vector4& out) const
{
    // Linear interpolation: out = this + t * (end - this)
    out.x = (end.x - this->x) * t + this->x;
    out.y = (end.y - this->y) * t + this->y;
    out.z = (end.z - this->z) * t + this->z;
    out.w = (end.w - this->w) * t + this->w;
}