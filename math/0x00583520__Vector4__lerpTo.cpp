// FUNC_NAME: Vector4::lerpTo
// Address: 0x00583520
// Role: Linear interpolation between this vector and a target vector, storing result in output.
// Assumes this, target, and out are pointers to 4-component float arrays (x, y, z, w).
// Offsets: this+0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w

void __thiscall Vector4::lerpTo(const Vector4 &target, Vector4 &out, float t) const
{
    float thisX = x;
    float thisY = y;
    float thisZ = z;
    float thisW = w;

    float targetX = target.x;
    float targetY = target.y;
    float targetZ = target.z;
    float targetW = target.w;

    out.x = (targetX - thisX) * t + thisX;
    out.y = (targetY - thisY) * t + thisY;
    out.z = (targetZ - thisZ) * t + thisZ;
    out.w = (targetW - thisW) * t + thisW;
}