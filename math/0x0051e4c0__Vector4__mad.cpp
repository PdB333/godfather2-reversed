// FUNC_NAME: Vector4::mad
// Address: 0x0051e4c0
// Role: Performs component-wise multiply-add: out = this * a + b
// Used for vector/quaternion blending or scaling operations

// Assuming float4 structure with x, y, z, w
struct Vector4 {
    float x, y, z, w;
};

// __thiscall: this pointer implicit
void __thiscall Vector4::mad(const Vector4& a, const Vector4& b, Vector4& out) const
{
    // Component-wise multiply-add: out = *this * a + b
    out.x = x * a.x + b.x;
    out.y = y * a.y + b.y;
    out.z = z * a.z + b.z;
    out.w = w * a.w + b.w;
}