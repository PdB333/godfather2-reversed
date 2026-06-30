// FUNC_NAME: Vector4::scaleAdd
// Address: 0x0052f960
// Role: Performs vector4 scale and add: out = (this * scalar) + addend
// Used for quaternion slerp or linear interpolation

void __thiscall Vector4::scaleAdd(const Vector4& addend, float scalar, Vector4& out) const
{
    // Component-wise: out[i] = this[i] * scalar + addend[i]
    out.x = this->x * scalar + addend.x; // +0x00
    out.y = this->y * scalar + addend.y; // +0x04
    out.z = this->z * scalar + addend.z; // +0x08
    out.w = this->w * scalar + addend.w; // +0x0C
}