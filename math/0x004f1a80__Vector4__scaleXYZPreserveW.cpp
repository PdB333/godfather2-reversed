// FUNC_NAME: Vector4::scaleXYZPreserveW
// Address: 0x004f1a80
// Scales the xyz components of this vector by a scalar from another vector, leaving w unchanged.
// This is used for operations where the w component (e.g., homogeneous coordinate) should not be modified.

class Vector4 {
    float m_data[4]; // +0x00: x, +0x04: y, +0x08: z, +0x0C: w

public:
    // Sets this vector's xyz to scaled xyz of src, w remains unchanged.
    void scaleXYZPreserveW(const Vector4& src, float scale) {
        this->m_data[0] = src.m_data[0] * scale;
        this->m_data[1] = src.m_data[1] * scale;
        this->m_data[2] = src.m_data[2] * scale;
        // m_data[3] (w) is not modified.
    }
};