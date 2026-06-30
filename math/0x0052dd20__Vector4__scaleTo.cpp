// FUNC_NAME: Vector4::scaleTo
// Address: 0x0052dd20
// Scales this 4-component vector by a scalar and writes to destination.
void __thiscall Vector4::scaleTo(float* dest, float scalar)
{
    // *in_EAX is the 'this' pointer, containing 4 floats at offsets 0,4,8,12
    float x = this->x;   // +0x00
    float y = this->y;   // +0x04
    float z = this->z;   // +0x08
    float w = this->w;   // +0x0C

    dest[0] = scalar * x;
    dest[1] = scalar * y;
    dest[2] = scalar * z;
    dest[3] = scalar * w;
}