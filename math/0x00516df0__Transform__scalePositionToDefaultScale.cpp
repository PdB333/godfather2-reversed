// FUNC_NAME: Transform::scalePositionToDefaultScale
// Address: 0x00516df0
// This function scales the position vector (first 4 floats) of a Transform object
// by the ratio of a global default scale to the object's own scale factor (offset 0x20).
// It is likely used to normalize or adjust the object's position to a standard scale.

extern const float g_defaultScale; // 0x00e2b1a4

class Transform
{
public:
    float m_position[4]; // +0x00 (position components: x, y, z, w)
    float m_rotation[4]; // +0x10 (quaternion: w, x, y, z)
    float m_scale;       // +0x20 (scale factor)

    void scalePositionToDefaultScale() // __thiscall
    {
        float scaleFactor = g_defaultScale / this->m_scale;
        m_position[0] *= scaleFactor;
        m_position[1] *= scaleFactor;
        m_position[2] *= scaleFactor;
        m_position[3] *= scaleFactor;
    }
};