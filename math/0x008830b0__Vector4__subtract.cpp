// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const Vector4* other, Vector4* result) const
{
    // this: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    // other: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    // result: +0x00 x, +0x04 y, +0x08 z, +0x0C w
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;
    float otherX = other->x;
    float otherY = other->y;
    float otherZ = other->z;
    float otherW = other->w;
    result->x = thisX - otherX;
    result->y = thisY - otherY;
    result->z = thisZ - otherZ;
    result->w = thisW - otherW;
}