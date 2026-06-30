// FUNC_NAME: Vector4::storeScaled
// Function address: 0x0066d2c0
// Writes scaled components of this vector (this = in_EAX) to output array.
// Offsets: this[0] +0x00, this[1] +0x04, this[2] +0x08, this[3] +0x0C
void __thiscall Vector4::storeScaled(float* outOutput, float scalar)
{
    float x = this->x;  // +0x00
    float y = this->y;  // +0x04
    float z = this->z;  // +0x08
    float w = this->w;  // +0x0C

    outOutput[0] = scalar * x;
    outOutput[1] = scalar * y;
    outOutput[2] = scalar * z;
    outOutput[3] = scalar * w;
}