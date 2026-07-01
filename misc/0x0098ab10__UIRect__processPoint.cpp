// FUNC_NAME: UIRect::processPoint
// Address: 0x0098ab10
// Role: Normalizes a point relative to a rectangle and applies a mapping/callback.

class UIRect {
public:
    // Offsets: +0x130 m_minX, +0x134 m_minY, +0x138 m_maxX, +0x13c m_maxY
    float m_minX;   // +0x130
    float m_minY;   // +0x134
    float m_maxX;   // +0x138
    float m_maxY;   // +0x13c

    // Normalizes point (x, y) to [0,1] within the rectangle, then maps and applies.
    void __thiscall processPoint(float x, float y) {
        // Normalize y to [0,1] relative to rectangle's Y range
        float normalizedY = (y - m_minY) / (m_maxY - m_minY);
        // Normalize x to [0,1] relative to rectangle's X range, pass normalizedY and its address to map function
        char result = mapNormalizedPoint((x - m_minX) / (m_maxX - m_minX), normalizedY, &normalizedY);
        if (result != 0) {
            applyMappedPoint(normalizedY);
        }
    }

private:
    // Maps normalized coordinates; returns non-zero if mapping succeeds, may modify outY.
    char __thiscall mapNormalizedPoint(float normalizedX, float normalizedY, float* outY);
    // Applies the mapped point (e.g., triggers an action).
    void __thiscall applyMappedPoint(float mappedValue);
};