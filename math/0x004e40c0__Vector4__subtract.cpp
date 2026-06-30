// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(float *this, float *other, float *result)
{
    float thisY = this[1];  // +0x04
    float thisZ = this[2];  // +0x08
    float thisW = this[3];  // +0x0C
    float otherY = other[1]; // +0x04
    float otherZ = other[2]; // +0x08
    float otherW = other[3]; // +0x0C

    // result = this - other
    result[0] = this[0] - other[0];  // x component
    result[1] = thisY - otherY;      // y component
    result[2] = thisZ - otherZ;      // z component
    result[3] = thisW - otherW;      // w component
}