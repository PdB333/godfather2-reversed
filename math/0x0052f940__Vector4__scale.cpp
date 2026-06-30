// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *dest, float scalar) const
{
    // Source vector's components (this) are implicitly pointed to by ECX (in_EAX)
    float x = this[0];  // +0x00
    float y = this[1];  // +0x04
    float z = this[2];  // +0x08
    float w = this[3];  // +0x0C

    dest[0] = scalar * x;
    dest[1] = scalar * y;
    dest[2] = scalar * z;
    dest[3] = scalar * w;
}