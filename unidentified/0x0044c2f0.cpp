// FUNC_0044c2f0: Vector4::cross

// Reconstructed cross product for 3D vectors (ignoring w)
// Takes this (implicit) as left operand, other as right operand,
// stores result in out. Sets out.w = 0.
void __thiscall Vector4::cross(const Vector4* other, Vector4* out) const {
    // this: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    // other: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    // out: same layout

    out->x = this->y * other->z - this->z * other->y;
    out->y = this->z * other->x - this->x * other->z;
    out->z = this->x * other->y - this->y * other->x;
    out->w = 0.0f; // original: fVar4*fVar8 - fVar4*fVar8 = 0
}