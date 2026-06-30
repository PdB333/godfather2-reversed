// FUNC_NAME: Vector4::componentMultiply
void __thiscall Vector4::componentMultiply(const float* otherVector, float* outResult) const
{
    // Multiply corresponding elements of two 4D vectors component-wise.
    // This: [x, y, z, w] at offsets +0x00, +0x04, +0x08, +0x0C
    outResult[0] = this[0] * otherVector[0]; // x * x
    outResult[1] = this[1] * otherVector[1]; // y * y
    outResult[2] = this[2] * otherVector[2]; // z * z
    outResult[3] = this[3] * otherVector[3]; // w * w
}