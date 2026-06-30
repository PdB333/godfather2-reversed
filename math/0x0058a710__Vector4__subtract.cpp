// FUNC_NAME: Vector4::subtract
// Address: 0x0058a710
// This is a __thiscall member function of a 4-component vector class.
// It computes: result = this - other (component-wise subtraction).

struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

void __thiscall Vector4::subtract(const Vector4& other, Vector4& result) const {
    float dx = this->x - other.x;
    float dy = this->y - other.y;
    float dz = this->z - other.z;
    float dw = this->w - other.w;
    result.x = dx;
    result.y = dy;
    result.z = dz;
    result.w = dw;
}