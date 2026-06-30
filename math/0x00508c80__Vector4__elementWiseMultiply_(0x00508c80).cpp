// FUNC_NAME: Vector4::elementWiseMultiply (0x00508c80)
// Performs component-wise (Hadamard) multiplication of two 4D vectors.
// this: left operand (in_EAX)
// param_1: right operand
// param_2: output vector
void __thiscall Vector4::elementWiseMultiply(const Vector4* right, Vector4* out) const
{
    // Multiply each component independently and store in out.
    out->x = this->x * right->x;
    out->y = this->y * right->y;
    out->z = this->z * right->z;
    out->w = this->w * right->w;
}