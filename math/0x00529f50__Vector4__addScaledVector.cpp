// FUNC_NAME: Vector4::addScaledVector
void __thiscall Vector4::addScaledVector(const Vector4& other, float scale, Vector4& outResult) const
{
    // result = this * scale + other
    outResult.x = scale * this->x + other.x;
    outResult.y = scale * this->y + other.y;
    outResult.z = scale * this->z + other.z;
    outResult.w = scale * this->w + other.w;
}