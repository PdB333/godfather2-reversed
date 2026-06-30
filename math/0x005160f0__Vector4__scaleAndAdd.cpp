// FUNC_NAME: Vector4::scaleAndAdd
// Function address: 0x005160f0
// Performs: out = scale * this + other (component-wise for 4D vector)
void __thiscall Vector4::scaleAndAdd(const Vector4& other, float scale, Vector4& out) const
{
    // this->m_x, m_y, m_z, m_w are the components of the current vector
    out.m_x = scale * this->m_x + other.m_x;
    out.m_y = scale * this->m_y + other.m_y;
    out.m_z = scale * this->m_z + other.m_z;
    out.m_w = scale * this->m_w + other.m_w;
}