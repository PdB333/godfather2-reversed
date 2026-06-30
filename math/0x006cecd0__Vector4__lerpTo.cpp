// FUNC_NAME: Vector4::lerpTo
// Address: 0x006cecd0
// Role: Linear interpolation between two 4-component vectors (e.g., quaternion or 4D vector)

void __thiscall Vector4::lerpTo(const Vector4& end, float t, Vector4& out) const
{
    // Read start vector (this) and end vector components
    float startX = this->x;   // +0x00
    float startY = this->y;   // +0x04
    float startZ = this->z;   // +0x08
    float startW = this->w;   // +0x0C

    float endX = end.x;       // +0x00
    float endY = end.y;       // +0x04
    float endZ = end.z;       // +0x08
    float endW = end.w;       // +0x0C

    out.x = (endX - startX) * t + startX;  // +0x00
    out.y = (endY - startY) * t + startY;  // +0x04
    out.z = (endZ - startZ) * t + startZ;  // +0x08
    out.w = (endW - startW) * t + startW;  // +0x0C
}