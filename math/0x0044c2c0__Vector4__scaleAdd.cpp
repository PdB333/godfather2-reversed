// FUNC_NAME: Vector4::scaleAdd
// Function at 0x0044c2c0: Vector4 scale-and-add operation: result = scale * this + other (4 components: x,y,z,w at offsets +0x00, +0x04, +0x08, +0x0C)
void __thiscall Vector4::scaleAdd(const Vector4& other, float scale, Vector4& result) const {
    result.x = scale * this->x + other.x;
    result.y = scale * this->y + other.y;
    result.z = scale * this->z + other.z;
    result.w = scale * this->w + other.w;
}