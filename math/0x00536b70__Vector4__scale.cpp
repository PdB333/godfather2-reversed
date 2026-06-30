// FUNC_NAME: Vector4::scale
// Address: 0x00536b70
// Multiplies each component of the 4D vector (this) by a scalar and stores the result in the output array.

void __thiscall Vector4::scale(float *out, float scalar) const
{
    // Read components from this (in_EAX)
    float x = this->x;   // +0x00
    float y = this->y;   // +0x04
    float z = this->z;   // +0x08
    float w = this->w;   // +0x0C

    // Write scaled components to output
    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}