// FUNC_NAME: Vector4::subtract
struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

void __thiscall Vector4::subtract(const Vector4& other, Vector4& out) const {
    out.x = this->x - other.x;
    out.y = this->y - other.y;
    out.z = this->z - other.z;
    out.w = this->w - other.w;
}