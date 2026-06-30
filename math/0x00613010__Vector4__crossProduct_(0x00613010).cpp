// FUNC_NAME: Vector4::crossProduct (0x00613010)
// Computes cross product of this vector and 'other', storing result in 'out' (w component = 0)
void __thiscall Vector4::crossProduct(const Vector4& other, Vector4& out) const
{
    // 'this' is the implicit first parameter (in_EAX)
    // 'other' is param_1
    // 'out' is param_2
    float aX = other.x;   // +0x00
    float aY = other.y;   // +0x04
    float aZ = other.z;   // +0x08
    float aW = other.w;   // +0x0C

    float bX = this->x;   // +0x00
    float bY = this->y;   // +0x04
    float bZ = this->z;   // +0x08
    float bW = this->w;   // +0x0C

    // Cross product components (ignoring w values)
    out.x = aY * bZ - aZ * bY;  // (a.y * b.z) - (a.z * b.y)
    out.y = aZ * bX - aX * bZ;  // (a.z * b.x) - (a.x * b.z)
    out.z = aX * bY - aY * bX;  // (a.x * b.y) - (a.y * b.x)
    out.w = aW * bW - aW * bW;  // always zero (a.w * b.w - a.w * b.w)
}