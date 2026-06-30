// FUNC_NAME: EARS::Math::Vector4::lerp
// Address: 0x00508b60
// Role: Linear interpolation between two 4-component vectors (quaternion or vector).
// Parameters:
//   other - source vector B (pointer to float[4])
//   t     - interpolation factor (0.0 returns this, 1.0 returns other)
//   out   - output vector (pointer to float[4])
// This is a __thiscall method on a 4-float vector class.

void __thiscall EARS::Math::Vector4::lerp(const Vector4* other, float t, float* out) const
{
    // Store components of this vector
    float ax = this->x; // offset +0x00
    float ay = this->y; // offset +0x04
    float az = this->z; // offset +0x08
    float aw = this->w; // offset +0x0C

    // Store components of the other vector
    float bx = other->x;
    float by = other->y;
    float bz = other->z;
    float bw = other->w;

    // Linear interpolation: out = this + (other - this) * t
    out[0] = ax + (bx - ax) * t;
    out[1] = ay + (by - ay) * t;
    out[2] = az + (bz - az) * t;
    out[3] = aw + (bw - aw) * t;
}