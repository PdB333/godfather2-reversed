// FUNC_NAME: Vector4::lerp
// Function at 0x0066daf0: Linear interpolation of 4D vectors (out = this * t + other)
// Assumes __thiscall with this as first vector, other as param_1, t as param_2, result as param_3
void __thiscall Vector4::lerp(const Vector4& other, float t, Vector4& out) const {
    // Load components from this (via in_EAX) and other (param_1)
    out.x = t * this->x + other.x;  // w0
    out.y = t * this->y + other.y;  // w1
    out.z = t * this->z + other.z;  // w2
    out.w = t * this->w + other.w;  // w3
}