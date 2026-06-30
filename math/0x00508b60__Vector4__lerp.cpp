// FUNC_NAME: Vector4::lerp

void __thiscall Vector4::lerp(const Vector4& target, float t, Vector4& out)
{
    float startX = this->x;
    float startY = this->y;
    float startZ = this->z;
    float startW = this->w;

    float endX = target.x;
    float endY = target.y;
    float endZ = target.z;
    float endW = target.w;

    out.x = (endX - startX) * t + startX;
    out.y = (endY - startY) * t + startY;
    out.z = (endZ - startZ) * t + startZ;
    out.w = (endW - startW) * t + startW;
}