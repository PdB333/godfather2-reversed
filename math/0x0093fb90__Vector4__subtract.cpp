// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const float* other, float* result) const
{
    // this (in_EAX) is the source vector, other (param_1) is the vector to subtract,
    // result (param_2) stores the difference.
    // Each vector has 4 float components at offsets 0x00, 0x04, 0x08, 0x0C.

    float srcX = this[0];  // +0x00
    float srcY = this[1];  // +0x04
    float srcZ = this[2];  // +0x08
    float srcW = this[3];  // +0x0C

    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    result[0] = srcX - otherX;
    result[1] = srcY - otherY;
    result[2] = srcZ - otherZ;
    result[3] = srcW - otherW;
}