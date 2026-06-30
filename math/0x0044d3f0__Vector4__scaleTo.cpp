// FUNC_NAME: Vector4::scaleTo
void __thiscall Vector4::scaleTo(float *dest, float scalar)
{
    // Read this vector's components
    float x = this->x;  // +0x00
    float y = this->y;  // +0x04
    float z = this->z;  // +0x08
    float w = this->w;  // +0x0C

    // Scale each component by scalar and store to destination
    dest[0] = scalar * x;
    dest[1] = scalar * y;
    dest[2] = scalar * z;
    dest[3] = scalar * w;
}