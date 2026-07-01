// FUNC_NAME: Vector4::scale

// Scale a 4-component vector by a scalar and store result in output.
// This function is a const member of Vector4 (or similar 4-float struct).
// Offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w
void __thiscall Vector4::scale(float *out, float scalar) const
{
    // Load source components from this (in_EAX)
    float sx = this->x;   // *in_EAX
    float sy = this->y;   // in_EAX[1]
    float sz = this->z;   // in_EAX[2]
    float sw = this->w;   // in_EAX[3]

    // Write scaled result to output
    out[0] = scalar * sx;
    out[1] = scalar * sy;
    out[2] = scalar * sz;
    out[3] = scalar * sw;
}