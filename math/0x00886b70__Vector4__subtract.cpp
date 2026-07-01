// FUNC_NAME: Vector4::subtract
// Address: 0x00886b70
// Role: Subtracts two 4-component vectors (this - other) and stores result in output.
void __thiscall Vector4::subtract(const float* other, float* out) const
{
    // Component-wise subtraction: out = this - other
    out[0] = this->m_data[0] - other[0]; // x
    out[1] = this->m_data[1] - other[1]; // y
    out[2] = this->m_data[2] - other[2]; // z
    out[3] = this->m_data[3] - other[3]; // w
}