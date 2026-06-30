// FUNC_NAME: Vector4::lerp
void __thiscall Vector4::lerp(const Vector4& other, float t, Vector4& out) const {
    // Linear interpolation of two 4D vectors: out = this * t + other
    // this: [x, y, z, w] (offsets +0x00, +0x04, +0x08, +0x0C)
    // other: [x, y, z, w]
    // t: interpolation factor
    // out: result vector
    out.x = t * this->x + other.x;
    out.y = t * this->y + other.y;
    out.z = t * this->z + other.z;
    out.w = t * this->w + other.w;
}