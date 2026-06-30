// FUNC_NAME: Vector4::scaleTo
void Vector4::scaleTo(float* dest, float scalar)
{
    dest[0] = scalar * this->x;   // +0x00
    dest[1] = scalar * this->y;   // +0x04
    dest[2] = scalar * this->z;   // +0x08
    dest[3] = scalar * this->w;   // +0x0C
}