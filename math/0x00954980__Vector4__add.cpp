// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(const float *other, float *result) {
    // this vector is accessed via in_EAX implicitly (the this pointer)
    // +0x00: x, +0x04: y, +0x08: z, +0x0C: w
    float thisX = this[0];
    float thisY = this[1];
    float thisZ = this[2];
    float thisW = this[3];
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];
    result[0] = thisX + otherX;
    result[1] = thisY + otherY;
    result[2] = thisZ + otherZ;
    result[3] = thisW + otherW;
}