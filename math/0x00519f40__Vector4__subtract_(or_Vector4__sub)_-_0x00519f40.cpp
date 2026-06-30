//FUNC_NAME: Vector4::subtract (or Vector4::sub) - 0x00519f40
// Subtracts another vector from this vector and stores result in output.
// this - other -> out
void __thiscall Vector4::subtract(const Vector4& other, Vector4& out) const
{
    // Component-wise subtraction of 4D vectors
    out.x = this->x - other.x;
    out.y = this->y - other.y;
    out.z = this->z - other.z;
    out.w = this->w - other.w;
}