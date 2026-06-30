// FUNC_NAME: Vector4::crossProduct
void __thiscall Vector4::crossProduct(const Vector4& other, Vector4& result) {
    // 'this' corresponds to the implicit ECX (in_EAX in decompiled).
    // param_1 is 'other', param_2 is 'result'. All are 4-float vectors.
    // Cross product computed on first three components, w set to 0.

    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w; // unused in calculation but loaded

    float otherX = other.x;
    float otherY = other.y;
    float otherZ = other.z;
    float otherW = other.w; // unused

    result.x = thisY * otherZ - thisZ * otherY;
    result.y = thisZ * otherX - thisX * otherZ;
    result.z = thisX * otherY - thisY * otherX;
    result.w = thisW * otherW - thisW * otherW; // always zero
}