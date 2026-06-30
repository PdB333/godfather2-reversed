// FUNC_NAME: Vector4::lerp

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

void __thiscall Vector4::lerp(const Vector4& to, float t, Vector4& result)
{
    // Linear interpolation: result = this + t * (to - this)
    float dx = to.x - this->x;
    float dy = to.y - this->y;
    float dz = to.z - this->z;
    float dw = to.w - this->w;

    result.x = this->x + dx * t;
    result.y = this->y + dy * t;
    result.z = this->z + dz * t;
    result.w = this->w + dw * t;
}