// FUNC_NAME: Vector4::add
// Address: 0x00508a50
// Role: Adds two 4-component vectors element-wise (this + other) and stores result in out.
// Class: Vector4 (x, y, z, w at offsets 0x00, 0x04, 0x08, 0x0C)
void __thiscall Vector4::add(const Vector4& other, Vector4& out) const {
    out.x = this->x + other.x;
    out.y = this->y + other.y;
    out.z = this->z + other.z;
    out.w = this->w + other.w;
}