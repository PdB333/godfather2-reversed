// FUNC_NAME: Vector4::scale
// Address: 0x0061c710
// Multiplies this vector (4 floats) by a scalar and stores result in output array.

void __thiscall Vector4::scale(float *out, float scalar) const
{
    out[0] = scalar * this->x;   // +0x00
    out[1] = scalar * this->y;   // +0x04
    out[2] = scalar * this->z;   // +0x08
    out[3] = scalar * this->w;   // +0x0C
}