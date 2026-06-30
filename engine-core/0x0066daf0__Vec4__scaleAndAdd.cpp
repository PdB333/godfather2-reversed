// FUNC_NAME: Vec4::scaleAndAdd
// Address: 0x0066daf0
// Role: Computes out = other + scale * this for a 4D vector.
// This is a member function of a Vec4 structure with float components [x, y, z, w].
void __thiscall Vec4::scaleAndAdd(const Vec4* other, float scale, Vec4* out) const
{
    // Load components of this (pointed by in_EAX)
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w; // +0x0C

    // Load components of other (param_1)
    float otherX = other->x; // +0x00
    float otherY = other->y; // +0x04
    float otherZ = other->z; // +0x08
    float otherW = other->w; // +0x0C

    // Compute out = other + scale * this
    out->x = otherX + scale * thisX; // +0x00
    out->y = otherY + scale * thisY; // +0x04
    out->z = otherZ + scale * thisZ; // +0x08
    out->w = otherW + scale * thisW; // +0x0C
}