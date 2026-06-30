// FUNC_NAME: Vector4::scale
// Function address: 0x006d0010
// Role: Scales a 4-component vector by a scalar and writes result to output.
// Class Vector4 assumed to have members: float x, y, z, w (offsets 0x00, 0x04, 0x08, 0x0C)

void __thiscall Vector4::scale(float *outVector, float scalar)
{
    float x = this->x; // +0x00
    float y = this->y; // +0x04
    float z = this->z; // +0x08
    float w = this->w; // +0x0C

    outVector[0] = scalar * x;
    outVector[1] = scalar * y;
    outVector[2] = scalar * z;
    outVector[3] = scalar * w;
}