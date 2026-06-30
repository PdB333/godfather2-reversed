// FUNC_NAME: Vector4::elementwiseMultiply
void __thiscall Vector4::elementwiseMultiply(const float *other, float *result)
{
    float thisY = this[1];
    float thisZ = this[2];
    float thisW = this[3];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    result[0] = this[0] * other[0];
    result[1] = thisY * otherY;
    result[2] = thisZ * otherZ;
    result[3] = thisW * otherW;
}