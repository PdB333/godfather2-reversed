// FUNC_NAME: Rect2D::setCorners

struct Vector2 {
    float x;
    float y;
};

// Class representing a 2D rectangle defined by four corner points.
// The four corners are stored at offsets +0x74, +0x7c, +0x84, +0x8c respectively.
// Each corner is a Vector2 (8 bytes).
class Rect2D {
public:
    // +0x74: m_topLeft
    // +0x7c: m_topRight
    // +0x84: m_bottomLeft
    // +0x8c: m_bottomRight
    Vector2 m_topLeft;
    Vector2 m_topRight;
    Vector2 m_bottomLeft;
    Vector2 m_bottomRight;

    // Copies an array of four Vector2 corners into the object's members.
    void setCorners(const Vector2 corners[4]) {
        m_topLeft = corners[0];
        m_topRight = corners[1];
        m_bottomLeft = corners[2];
        m_bottomRight = corners[3];
    }
};