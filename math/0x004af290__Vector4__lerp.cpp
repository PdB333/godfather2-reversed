// FUNC_NAME: Vector4::lerp
// Function address: 0x004af290
// Role: Linear interpolation between two four-component vectors.
// Computes out = this * (1 - t) + target * t, storing result in external buffer.

void __thiscall Vector4::lerp(const Vector4& target, float t, Vector4& out) const
{
    // +0x00: x, +0x04: y, +0x08: z, +0x0C: w
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    float targetX = target.x;
    float targetY = target.y;
    float targetZ = target.z;
    float targetW = target.w;

    // Linear interpolation: out = this + (target - this) * t
    out.x = (targetX - thisX) * t + thisX;
    out.y = (targetY - thisY) * t + thisY;
    out.z = (targetZ - thisZ) * t + thisZ;
    out.w = (targetW - thisW) * t + thisW;
}