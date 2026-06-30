// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const Vector4& other, Vector4& result) const {
    // this -> x, y, z, w (offsets 0x00, 0x04, 0x08, 0x0C)
    // other -> x, y, z, w
    // result -> x, y, z, w
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    result.z = this->z - other.z;
    result.w = this->w - other.w;
}