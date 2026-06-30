// FUNC_NAME: Float4::multiplyElementWise

// Reconstructed member function for element-wise multiplication of two 4-component vectors (e.g., quaternion or vector4).
// This = first operand (input A), param1 = second operand (input B), param2 = output (result = A * B element-wise).
// Struct Float4: +0x00 x, +0x04 y, +0x08 z, +0x0C w
void __thiscall Float4::multiplyElementWise(const Float4* other, Float4* out) const
{
    out->x = this->x * other->x;
    out->y = this->y * other->y;
    out->z = this->z * other->z;
    out->w = this->w * other->w;
}