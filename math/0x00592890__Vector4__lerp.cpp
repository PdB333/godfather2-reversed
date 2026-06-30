// FUNC_NAME: Vector4::lerp
// Address: 0x00592890
// Role: Linear interpolation between two 4-component vectors (e.g., quaternions or positions)
// This is a member function of a Vector4 class that stores 4 floats.
void __thiscall Vector4::lerp(const Vector4& other, float t, Vector4& out) const
{
    // this->data[0..3] is the source vector
    // other.data[0..3] is the destination vector
    // t is the interpolation factor (0 = this, 1 = other)
    // out receives the interpolated result
    out.data[0] = (other.data[0] - this->data[0]) * t + this->data[0];
    out.data[1] = (other.data[1] - this->data[1]) * t + this->data[1];
    out.data[2] = (other.data[2] - this->data[2]) * t + this->data[2];
    out.data[3] = (other.data[3] - this->data[3]) * t + this->data[3];
}