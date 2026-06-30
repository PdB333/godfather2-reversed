// FUNC_NAME: Vector4::componentWiseMultiply
void __thiscall Vector4::componentWiseMultiply(const Vector4& other, Vector4& result) const
{
    // Component-wise multiplication (Hadamard product) of this vector and other, storing in result
    // Field offsets: +0x00 = x, +0x04 = y, +0x08 = z, +0x0C = w (float)
    float thisY = this->y; // equivalent to in_EAX[1]
    float thisZ = this->z; // in_EAX[2]
    float thisW = this->w; // in_EAX[3]
    float otherY = other.y; // param_1[1]
    float otherZ = other.z; // param_1[2]
    float otherW = other.w; // param_1[3]

    result.x = this->x * other.x; // *in_EAX * *param_1
    result.y = thisY * otherY;
    result.z = thisZ * otherZ;
    result.w = thisW * otherW;
}