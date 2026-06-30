// FUNC_NAME: Vector4::scaleTo
void __thiscall Vector4::scaleTo(float *out, float scalar) const
{
    // Multiplies each component of the vector by scalar and stores to output.
    // Offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    out[0] = scalar * this->x;
    out[1] = scalar * this->y;
    out[2] = scalar * this->z;
    out[3] = scalar * this->w;
}