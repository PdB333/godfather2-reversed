// FUNC_NAME: Vector4::lerpTo
// Address: 0x00583140
// Role: Linear interpolation between two 4D vectors.
//   this -> source (start) vector
//   param_1 -> target (end) vector
//   param_2 -> output (result) vector
//   param_3 -> interpolation factor t [0,1]

struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    void __thiscall lerpTo(const Vector4& to, Vector4& result, float t) const {
        // result = this + (to - this) * t
        result.x = (to.x - this->x) * t + this->x;
        result.y = (to.y - this->y) * t + this->y;
        result.z = (to.z - this->z) * t + this->z;
        result.w = (to.w - this->w) * t + this->w;
    }
};