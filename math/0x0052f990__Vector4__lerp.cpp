// FUNC_NAME: Vector4::lerp
// Function address: 0x0052f990
// Linear interpolation between this vector and a target vector.
// result = this + t * (target - this)
void __thiscall Vector4::lerp(const Vector4& target, float t, Vector4& result) const
{
    // Interpolate each component
    result.x = x + t * (target.x - x);
    result.y = y + t * (target.y - y);
    result.z = z + t * (target.z - z);
    result.w = w + t * (target.w - w);
}