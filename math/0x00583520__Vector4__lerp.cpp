// FUNC_NAME: Vector4::lerp
// Function address: 0x00583520
// Role: Linear interpolation between two 4-component vectors (e.g., quaternions or 4D positions).
// Stores result in output vector: out = this + (to - this) * t

void __thiscall Vector4::lerp(const Vector4& to, Vector4& out, float t) const
{
    // Interpolate each component
    out.x = (to.x - this->x) * t + this->x;
    out.y = (to.y - this->y) * t + this->y;
    out.z = (to.z - this->z) * t + this->z;
    out.w = (to.w - this->w) * t + this->w;
}