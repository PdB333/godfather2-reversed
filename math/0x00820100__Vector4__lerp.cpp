// FUNC_NAME: Vector4::lerp
// Address: 0x00820100
// Role: Linear interpolation of two 4-component vectors (quaternions or positions).
// This is a __thiscall member function of a 4-float structure (likely Vector4 or Quaternion).
// The this pointer is the source vector, param_1 is the target, param_2 is factor t, param_3 is output.

struct Vector4 {
    float f[4]; // x, y, z, w
};

void __thiscall Vector4::lerp(const Vector4& target, float t, Vector4& out) const {
    // Component-wise lerp: out[i] = (target[i] - this[i]) * t + this[i]
    out.f[0] = (target.f[0] - this->f[0]) * t + this->f[0];
    out.f[1] = (target.f[1] - this->f[1]) * t + this->f[1];
    out.f[2] = (target.f[2] - this->f[2]) * t + this->f[2];
    out.f[3] = (target.f[3] - this->f[3]) * t + this->f[3];
}