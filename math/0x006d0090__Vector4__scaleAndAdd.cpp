// FUNC_NAME: Vector4::scaleAndAdd
void __thiscall Vector4::scaleAndAdd(const Vector4& other, float factor, Vector4& result) const
{
    // this: pointer to 4 floats at offsets +0x00, +0x04, +0x08, +0x0C
    // other: pointer to 4 floats at offsets +0x00, +0x04, +0x08, +0x0C
    // factor: scalar multiplier
    // result: output vector (4 floats)
    // Operation: result = factor * this + other (component-wise linear combination)

    result.x = factor * this->x + other.x;
    result.y = factor * this->y + other.y;
    result.z = factor * this->z + other.z;
    result.w = factor * this->w + other.w;
}