// FUNC_NAME: Vector4::multiply
void __thiscall Vector4::multiply(const Vector4& other, Vector4& out) const
{
    // Component-wise multiplication of two 4D vectors.
    // this = [x, y, z, w] at offsets +0x00, +0x04, +0x08, +0x0C
    // other = [x, y, z, w] similarly
    out.x = x * other.x;
    out.y = y * other.y;
    out.z = z * other.z;
    out.w = w * other.w;
}