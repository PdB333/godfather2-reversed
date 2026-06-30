// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *dst, float scalar) const
{
    // Scale 4-component vector (x,y,z,w) by scalar, write result to dst
    dst[0] = scalar * v[0];
    dst[1] = scalar * v[1];
    dst[2] = scalar * v[2];
    dst[3] = scalar * v[3];
}