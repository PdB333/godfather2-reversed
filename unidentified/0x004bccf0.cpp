// FUN_004bccf0: Vector4::scaleAndAdd
// Multiplies this vector by a scalar and adds another vector, storing result in output.
// out = scalar * this + other
void __thiscall Vector4::scaleAndAdd(const Vector4& other, float scalar, Vector4& out) const
{
    // this: points to 4 floats (x, y, z, w) at offsets +0x00, +0x04, +0x08, +0x0C
    // other: also a Vector4
    // scalar: float factor to multiply this vector
    // out: reference to output Vector4

    out.x = scalar * x + other.x;
    out.y = scalar * y + other.y;
    out.z = scalar * z + other.z;
    out.w = scalar * w + other.w;
}