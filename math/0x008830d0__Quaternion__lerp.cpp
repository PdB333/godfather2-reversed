// FUNC_NAME: Quaternion::lerp
// Function address: 0x008830d0
// Linearly blends two quaternions: out = this * factor + to (simple linear combination, not spherical)
void __thiscall Quaternion::lerp(const Quaternion& to, float factor, Quaternion& out) const
{
    out.x = factor * this->x + to.x;
    out.y = factor * this->y + to.y;
    out.z = factor * this->z + to.z;
    out.w = factor * this->w + to.w;
}