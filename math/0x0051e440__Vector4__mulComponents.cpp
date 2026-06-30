// FUNC_NAME: Vector4::mulComponents
void __thiscall Vector4::mulComponents(const float *other, float *result) const
{
    // Component-wise multiplication of two 4D vectors
    // 'this' is the first operand (4 floats at offset 0,4,8,12)
    // other is second operand, result is output
    float ax = this[1];     // this.y (offset +4)
    float ay = this[2];     // this.z (offset +8)
    float az = this[3];     // this.w (offset +12)
    float bx = other[1];    // other.y
    float by = other[2];    // other.z
    float bz = other[3];    // other.w
    *result       = *this * *other;   // x = this.x * other.x
    result[1] = ax * bx;               // y = this.y * other.y
    result[2] = ay * by;               // z = this.z * other.z
    result[3] = az * bz;               // w = this.w * other.w
}