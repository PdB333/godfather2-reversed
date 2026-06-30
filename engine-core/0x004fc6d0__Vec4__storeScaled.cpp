// FUNC_NAME: Vec4::storeScaled
// Address: 0x004fc6d0
// Role: Multiplies the vector (this) by a scalar and stores the result in output vector.
// Offsets: +0x0 = x, +0x4 = y, +0x8 = z, +0xC = w

void __thiscall Vec4::storeScaled(Vec4* outVec, float scalar)
{
    // Read components from this (in_EAX)
    float x = this->x;   // +0x0
    float y = this->y;   // +0x4
    float z = this->z;   // +0x8
    float w = this->w;   // +0xC

    // Write scaled components to output
    outVec->x = scalar * x;
    outVec->y = scalar * y;
    outVec->z = scalar * z;
    outVec->w = scalar * w;

    return;
}