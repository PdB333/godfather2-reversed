// FUNC_NAME: Vector4::lerp

// Function address: 0x00578180
// Role: Linear interpolation between two 4-component vectors.
// This is a member function of a Vector4 class. The interpolation is
// performed in place: output = this * (1 - t) + target * t, which is
// rearranged as this + (target - this) * t for numeric stability.

class Vector4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    // Interpolates from this vector towards target by factor t (0..1).
    // Result is stored in output.
    void lerp(const Vector4& target, float t, Vector4& output) const;
};

void Vector4::lerp(const Vector4& target, float t, Vector4& output) const {
    output.x = (target.x - this->x) * t + this->x;
    output.y = (target.y - this->y) * t + this->y;
    output.z = (target.z - this->z) * t + this->z;
    output.w = (target.w - this->w) * t + this->w;
}