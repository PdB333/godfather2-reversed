// FUNC_NAME: Vector4::scaleAdd
// Function address: 0x00508b00
// Role: Performs multiply-add: result = scale * this + other (element-wise for 4 floats).
void __thiscall Vector4::scaleAdd(const Vector4& other, float scale, Vector4& out) const {
    out.x = scale * x + other.x;
    out.y = scale * y + other.y;
    out.z = scale * z + other.z;
    out.w = scale * w + other.w;
}