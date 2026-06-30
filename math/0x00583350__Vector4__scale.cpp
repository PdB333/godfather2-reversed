// FUNC_NAME: Vector4::scale
// Address: 0x00583350
// Role: Scales the vector (x,y,z,w) by scalar, writing result to output array.
void __thiscall Vector4::scale(float *out, float scalar) const {
    // Class layout: m_components[0] at +0x00, [1] at +0x04, [2] at +0x08, [3] at +0x0C
    float x = this->m_components[0];
    float y = this->m_components[1];
    float z = this->m_components[2];
    float w = this->m_components[3];
    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}