// FUNC_NAME: Vector4::blend
// Address: 0x00825310
// Role: Performs a weighted blend of two 4D vectors (or quaternion linear interpolation).
// Computes result = other + t * this, where 'this' is the vector to scale.
// Typically used for smooth interpolation between vector states.

struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

void __thiscall Vector4::blend(const Vector4& other, float t, Vector4& result) const {
    // result = other + t * this
    result.x = t * x + other.x;
    result.y = t * y + other.y;
    result.z = t * z + other.z;
    result.w = t * w + other.w;
}