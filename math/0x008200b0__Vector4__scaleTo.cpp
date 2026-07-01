// FUNC_NAME: Vector4::scaleTo
void __thiscall Vector4::scaleTo(float *out, float scalar) const
{
    // Scale this vector by scalar and store result in out
    out[0] = scalar * this->x; // +0x00
    out[1] = scalar * this->y; // +0x04
    out[2] = scalar * this->z; // +0x08
    out[3] = scalar * this->w; // +0x0C
}