// FUNC_NAME: GameObject::setTransform
// Reconstructed C++ for setting object transform (position, rotation quaternion, scale)
// Address: 0x0055ae90

struct D3DXVECTOR4 {
    float x, y, z, w;
};

// Unknown class with transform data at offsets 0x10, 0x20, 0x30
class GameObject {
    // vtable pointer at +0x00
    // ... other members up to +0x0F
    // +0x10: D3DXVECTOR4 m_position
    // +0x20: D3DXVECTOR4 m_rotation (quaternion)
    // +0x30: float m_scale

public:
    // Copy two 4-float vectors and one float into the object's transform fields
    void __thiscall setTransform(const D3DXVECTOR4* position, const D3DXVECTOR4* rotation, float scale) {
        // Store position (4 floats) at +0x10
        this->m_position.x = position->x;
        this->m_position.y = position->y;
        this->m_position.z = position->z;
        this->m_position.w = position->w;

        // Store rotation quaternion (4 floats) at +0x20
        this->m_rotation.x = rotation->x;
        this->m_rotation.y = rotation->y;
        this->m_rotation.z = rotation->z;
        this->m_rotation.w = rotation->w;

        // Store uniform scale at +0x30
        this->m_scale = scale;
    }
};