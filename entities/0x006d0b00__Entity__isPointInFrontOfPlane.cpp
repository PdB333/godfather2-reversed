// FUNC_NAME: Entity::isPointInFrontOfPlane
// Function address: 0x006d0b00
// Role: Check if a 2D point (x, z) is in front of the entity's facing direction within a global distance threshold.

extern float gs_fDistThreshold; // _DAT_00d577a0 - global threshold for "in front" distance

class Entity {
public:
    // __thiscall
    bool isPointInFrontOfPlane(const float* point) const {
        // point[0] = x, point[1] = y (ignored), point[2] = z
        // Entity position (x, z) at offsets +0x10, +0x18
        // Entity facing direction (x, z) at offsets +0x50, +0x58
        float dot = m_facingDirX * (point[0] - m_positionX) + 
                    m_facingDirZ * (point[2] - m_positionZ);
        return dot > gs_fDistThreshold;
    }

private:
    float m_positionX; // +0x10
    // float m_positionY; // +0x14 (unused)
    float m_positionZ; // +0x18
    // ... (other fields)
    float m_facingDirX; // +0x50
    // float m_facingDirY; // +0x54 (unused)
    float m_facingDirZ; // +0x58
};